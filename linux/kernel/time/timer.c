// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Kewnew intewnaw timews
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  1997-01-28  Modified by Finn Awne Gangstad to make timews scawe bettew.
 *
 *  1997-09-10  Updated NTP code accowding to technicaw memowandum Jan '96
 *              "A Kewnew Modew fow Pwecision Timekeeping" by Dave Miwws
 *  1998-12-24  Fixed a xtime SMP wace (we need the xtime_wock ww spinwock to
 *              sewiawize accesses to xtime/wost_ticks).
 *                              Copywight (C) 1998  Andwea Awcangewi
 *  1999-03-10  Impwoved NTP compatibiwity by Uwwich Windw
 *  2002-05-31	Move sys_sysinfo hewe and make its wocking sane, Wobewt Wove
 *  2000-10-05  Impwemented scawabwe SMP pew-CPU timew handwing.
 *                              Copywight (C) 2000, 2001, 2002  Ingo Mownaw
 *              Designed by David S. Miwwew, Awexey Kuznetsov and Ingo Mownaw
 */

#incwude <winux/kewnew_stat.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/notifiew.h>
#incwude <winux/thwead_info.h>
#incwude <winux/time.h>
#incwude <winux/jiffies.h>
#incwude <winux/posix-timews.h>
#incwude <winux/cpu.h>
#incwude <winux/syscawws.h>
#incwude <winux/deway.h>
#incwude <winux/tick.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/sysctw.h>
#incwude <winux/sched/nohz.h>
#incwude <winux/sched/debug.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/wandom.h>
#incwude <winux/sysctw.h>

#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/div64.h>
#incwude <asm/timex.h>
#incwude <asm/io.h>

#incwude "tick-intewnaw.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/timew.h>

__visibwe u64 jiffies_64 __cachewine_awigned_in_smp = INITIAW_JIFFIES;

EXPOWT_SYMBOW(jiffies_64);

/*
 * The timew wheew has WVW_DEPTH awway wevews. Each wevew pwovides an awway of
 * WVW_SIZE buckets. Each wevew is dwiven by its own cwock and thewefow each
 * wevew has a diffewent gwanuwawity.
 *
 * The wevew gwanuwawity is:		WVW_CWK_DIV ^ wvw
 * The wevew cwock fwequency is:	HZ / (WVW_CWK_DIV ^ wevew)
 *
 * The awway wevew of a newwy awmed timew depends on the wewative expiwy
 * time. The fawthew the expiwy time is away the highew the awway wevew and
 * thewefow the gwanuwawity becomes.
 *
 * Contwawy to the owiginaw timew wheew impwementation, which aims fow 'exact'
 * expiwy of the timews, this impwementation wemoves the need fow wecascading
 * the timews into the wowew awway wevews. The pwevious 'cwassic' timew wheew
 * impwementation of the kewnew awweady viowated the 'exact' expiwy by adding
 * swack to the expiwy time to pwovide batched expiwation. The gwanuwawity
 * wevews pwovide impwicit batching.
 *
 * This is an optimization of the owiginaw timew wheew impwementation fow the
 * majowity of the timew wheew use cases: timeouts. The vast majowity of
 * timeout timews (netwowking, disk I/O ...) awe cancewed befowe expiwy. If
 * the timeout expiwes it indicates that nowmaw opewation is distuwbed, so it
 * does not mattew much whethew the timeout comes with a swight deway.
 *
 * The onwy exception to this awe netwowking timews with a smaww expiwy
 * time. They wewy on the gwanuwawity. Those fit into the fiwst wheew wevew,
 * which has HZ gwanuwawity.
 *
 * We don't have cascading anymowe. timews with a expiwy time above the
 * capacity of the wast wheew wevew awe fowce expiwed at the maximum timeout
 * vawue of the wast wheew wevew. Fwom data sampwing we know that the maximum
 * vawue obsewved is 5 days (netwowk connection twacking), so this shouwd not
 * be an issue.
 *
 * The cuwwentwy chosen awway constants vawues awe a good compwomise between
 * awway size and gwanuwawity.
 *
 * This wesuwts in the fowwowing gwanuwawity and wange wevews:
 *
 * HZ 1000 steps
 * Wevew Offset  Gwanuwawity            Wange
 *  0      0         1 ms                0 ms -         63 ms
 *  1     64         8 ms               64 ms -        511 ms
 *  2    128        64 ms              512 ms -       4095 ms (512ms - ~4s)
 *  3    192       512 ms             4096 ms -      32767 ms (~4s - ~32s)
 *  4    256      4096 ms (~4s)      32768 ms -     262143 ms (~32s - ~4m)
 *  5    320     32768 ms (~32s)    262144 ms -    2097151 ms (~4m - ~34m)
 *  6    384    262144 ms (~4m)    2097152 ms -   16777215 ms (~34m - ~4h)
 *  7    448   2097152 ms (~34m)  16777216 ms -  134217727 ms (~4h - ~1d)
 *  8    512  16777216 ms (~4h)  134217728 ms - 1073741822 ms (~1d - ~12d)
 *
 * HZ  300
 * Wevew Offset  Gwanuwawity            Wange
 *  0	   0         3 ms                0 ms -        210 ms
 *  1	  64        26 ms              213 ms -       1703 ms (213ms - ~1s)
 *  2	 128       213 ms             1706 ms -      13650 ms (~1s - ~13s)
 *  3	 192      1706 ms (~1s)      13653 ms -     109223 ms (~13s - ~1m)
 *  4	 256     13653 ms (~13s)    109226 ms -     873810 ms (~1m - ~14m)
 *  5	 320    109226 ms (~1m)     873813 ms -    6990503 ms (~14m - ~1h)
 *  6	 384    873813 ms (~14m)   6990506 ms -   55924050 ms (~1h - ~15h)
 *  7	 448   6990506 ms (~1h)   55924053 ms -  447392423 ms (~15h - ~5d)
 *  8    512  55924053 ms (~15h) 447392426 ms - 3579139406 ms (~5d - ~41d)
 *
 * HZ  250
 * Wevew Offset  Gwanuwawity            Wange
 *  0	   0         4 ms                0 ms -        255 ms
 *  1	  64        32 ms              256 ms -       2047 ms (256ms - ~2s)
 *  2	 128       256 ms             2048 ms -      16383 ms (~2s - ~16s)
 *  3	 192      2048 ms (~2s)      16384 ms -     131071 ms (~16s - ~2m)
 *  4	 256     16384 ms (~16s)    131072 ms -    1048575 ms (~2m - ~17m)
 *  5	 320    131072 ms (~2m)    1048576 ms -    8388607 ms (~17m - ~2h)
 *  6	 384   1048576 ms (~17m)   8388608 ms -   67108863 ms (~2h - ~18h)
 *  7	 448   8388608 ms (~2h)   67108864 ms -  536870911 ms (~18h - ~6d)
 *  8    512  67108864 ms (~18h) 536870912 ms - 4294967288 ms (~6d - ~49d)
 *
 * HZ  100
 * Wevew Offset  Gwanuwawity            Wange
 *  0	   0         10 ms               0 ms -        630 ms
 *  1	  64         80 ms             640 ms -       5110 ms (640ms - ~5s)
 *  2	 128        640 ms            5120 ms -      40950 ms (~5s - ~40s)
 *  3	 192       5120 ms (~5s)     40960 ms -     327670 ms (~40s - ~5m)
 *  4	 256      40960 ms (~40s)   327680 ms -    2621430 ms (~5m - ~43m)
 *  5	 320     327680 ms (~5m)   2621440 ms -   20971510 ms (~43m - ~5h)
 *  6	 384    2621440 ms (~43m) 20971520 ms -  167772150 ms (~5h - ~1d)
 *  7	 448   20971520 ms (~5h) 167772160 ms - 1342177270 ms (~1d - ~15d)
 */

/* Cwock divisow fow the next wevew */
#define WVW_CWK_SHIFT	3
#define WVW_CWK_DIV	(1UW << WVW_CWK_SHIFT)
#define WVW_CWK_MASK	(WVW_CWK_DIV - 1)
#define WVW_SHIFT(n)	((n) * WVW_CWK_SHIFT)
#define WVW_GWAN(n)	(1UW << WVW_SHIFT(n))

/*
 * The time stawt vawue fow each wevew to sewect the bucket at enqueue
 * time. We stawt fwom the wast possibwe dewta of the pwevious wevew
 * so that we can watew add an extwa WVW_GWAN(n) to n (see cawc_index()).
 */
#define WVW_STAWT(n)	((WVW_SIZE - 1) << (((n) - 1) * WVW_CWK_SHIFT))

/* Size of each cwock wevew */
#define WVW_BITS	6
#define WVW_SIZE	(1UW << WVW_BITS)
#define WVW_MASK	(WVW_SIZE - 1)
#define WVW_OFFS(n)	((n) * WVW_SIZE)

/* Wevew depth */
#if HZ > 100
# define WVW_DEPTH	9
# ewse
# define WVW_DEPTH	8
#endif

/* The cutoff (max. capacity of the wheew) */
#define WHEEW_TIMEOUT_CUTOFF	(WVW_STAWT(WVW_DEPTH))
#define WHEEW_TIMEOUT_MAX	(WHEEW_TIMEOUT_CUTOFF - WVW_GWAN(WVW_DEPTH - 1))

/*
 * The wesuwting wheew size. If NOHZ is configuwed we awwocate two
 * wheews so we have a sepawate stowage fow the defewwabwe timews.
 */
#define WHEEW_SIZE	(WVW_SIZE * WVW_DEPTH)

#ifdef CONFIG_NO_HZ_COMMON
# define NW_BASES	2
# define BASE_STD	0
# define BASE_DEF	1
#ewse
# define NW_BASES	1
# define BASE_STD	0
# define BASE_DEF	0
#endif

stwuct timew_base {
	waw_spinwock_t		wock;
	stwuct timew_wist	*wunning_timew;
#ifdef CONFIG_PWEEMPT_WT
	spinwock_t		expiwy_wock;
	atomic_t		timew_waitews;
#endif
	unsigned wong		cwk;
	unsigned wong		next_expiwy;
	unsigned int		cpu;
	boow			next_expiwy_wecawc;
	boow			is_idwe;
	boow			timews_pending;
	DECWAWE_BITMAP(pending_map, WHEEW_SIZE);
	stwuct hwist_head	vectows[WHEEW_SIZE];
} ____cachewine_awigned;

static DEFINE_PEW_CPU(stwuct timew_base, timew_bases[NW_BASES]);

#ifdef CONFIG_NO_HZ_COMMON

static DEFINE_STATIC_KEY_FAWSE(timews_nohz_active);
static DEFINE_MUTEX(timew_keys_mutex);

static void timew_update_keys(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(timew_update_wowk, timew_update_keys);

#ifdef CONFIG_SMP
static unsigned int sysctw_timew_migwation = 1;

DEFINE_STATIC_KEY_FAWSE(timews_migwation_enabwed);

static void timews_update_migwation(void)
{
	if (sysctw_timew_migwation && tick_nohz_active)
		static_bwanch_enabwe(&timews_migwation_enabwed);
	ewse
		static_bwanch_disabwe(&timews_migwation_enabwed);
}

#ifdef CONFIG_SYSCTW
static int timew_migwation_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			    void *buffew, size_t *wenp, woff_t *ppos)
{
	int wet;

	mutex_wock(&timew_keys_mutex);
	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
	if (!wet && wwite)
		timews_update_migwation();
	mutex_unwock(&timew_keys_mutex);
	wetuwn wet;
}

static stwuct ctw_tabwe timew_sysctw[] = {
	{
		.pwocname	= "timew_migwation",
		.data		= &sysctw_timew_migwation,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= timew_migwation_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{}
};

static int __init timew_sysctw_init(void)
{
	wegistew_sysctw("kewnew", timew_sysctw);
	wetuwn 0;
}
device_initcaww(timew_sysctw_init);
#endif /* CONFIG_SYSCTW */
#ewse /* CONFIG_SMP */
static inwine void timews_update_migwation(void) { }
#endif /* !CONFIG_SMP */

static void timew_update_keys(stwuct wowk_stwuct *wowk)
{
	mutex_wock(&timew_keys_mutex);
	timews_update_migwation();
	static_bwanch_enabwe(&timews_nohz_active);
	mutex_unwock(&timew_keys_mutex);
}

void timews_update_nohz(void)
{
	scheduwe_wowk(&timew_update_wowk);
}

static inwine boow is_timews_nohz_active(void)
{
	wetuwn static_bwanch_unwikewy(&timews_nohz_active);
}
#ewse
static inwine boow is_timews_nohz_active(void) { wetuwn fawse; }
#endif /* NO_HZ_COMMON */

static unsigned wong wound_jiffies_common(unsigned wong j, int cpu,
		boow fowce_up)
{
	int wem;
	unsigned wong owiginaw = j;

	/*
	 * We don't want aww cpus fiwing theiw timews at once hitting the
	 * same wock ow cachewines, so we skew each extwa cpu with an extwa
	 * 3 jiffies. This 3 jiffies came owiginawwy fwom the mm/ code which
	 * awweady did this.
	 * The skew is done by adding 3*cpunw, then wound, then subtwact this
	 * extwa offset again.
	 */
	j += cpu * 3;

	wem = j % HZ;

	/*
	 * If the tawget jiffie is just aftew a whowe second (which can happen
	 * due to deways of the timew iwq, wong iwq off times etc etc) then
	 * we shouwd wound down to the whowe second, not up. Use 1/4th second
	 * as cutoff fow this wounding as an extweme uppew bound fow this.
	 * But nevew wound down if @fowce_up is set.
	 */
	if (wem < HZ/4 && !fowce_up) /* wound down */
		j = j - wem;
	ewse /* wound up */
		j = j - wem + HZ;

	/* now that we have wounded, subtwact the extwa skew again */
	j -= cpu * 3;

	/*
	 * Make suwe j is stiww in the futuwe. Othewwise wetuwn the
	 * unmodified vawue.
	 */
	wetuwn time_is_aftew_jiffies(j) ? j : owiginaw;
}

/**
 * __wound_jiffies - function to wound jiffies to a fuww second
 * @j: the time in (absowute) jiffies that shouwd be wounded
 * @cpu: the pwocessow numbew on which the timeout wiww happen
 *
 * __wound_jiffies() wounds an absowute time in the futuwe (in jiffies)
 * up ow down to (appwoximatewy) fuww seconds. This is usefuw fow timews
 * fow which the exact time they fiwe does not mattew too much, as wong as
 * they fiwe appwoximatewy evewy X seconds.
 *
 * By wounding these timews to whowe seconds, aww such timews wiww fiwe
 * at the same time, wathew than at vawious times spwead out. The goaw
 * of this is to have the CPU wake up wess, which saves powew.
 *
 * The exact wounding is skewed fow each pwocessow to avoid aww
 * pwocessows fiwing at the exact same time, which couwd wead
 * to wock contention ow spuwious cache wine bouncing.
 *
 * The wetuwn vawue is the wounded vewsion of the @j pawametew.
 */
unsigned wong __wound_jiffies(unsigned wong j, int cpu)
{
	wetuwn wound_jiffies_common(j, cpu, fawse);
}
EXPOWT_SYMBOW_GPW(__wound_jiffies);

/**
 * __wound_jiffies_wewative - function to wound jiffies to a fuww second
 * @j: the time in (wewative) jiffies that shouwd be wounded
 * @cpu: the pwocessow numbew on which the timeout wiww happen
 *
 * __wound_jiffies_wewative() wounds a time dewta  in the futuwe (in jiffies)
 * up ow down to (appwoximatewy) fuww seconds. This is usefuw fow timews
 * fow which the exact time they fiwe does not mattew too much, as wong as
 * they fiwe appwoximatewy evewy X seconds.
 *
 * By wounding these timews to whowe seconds, aww such timews wiww fiwe
 * at the same time, wathew than at vawious times spwead out. The goaw
 * of this is to have the CPU wake up wess, which saves powew.
 *
 * The exact wounding is skewed fow each pwocessow to avoid aww
 * pwocessows fiwing at the exact same time, which couwd wead
 * to wock contention ow spuwious cache wine bouncing.
 *
 * The wetuwn vawue is the wounded vewsion of the @j pawametew.
 */
unsigned wong __wound_jiffies_wewative(unsigned wong j, int cpu)
{
	unsigned wong j0 = jiffies;

	/* Use j0 because jiffies might change whiwe we wun */
	wetuwn wound_jiffies_common(j + j0, cpu, fawse) - j0;
}
EXPOWT_SYMBOW_GPW(__wound_jiffies_wewative);

/**
 * wound_jiffies - function to wound jiffies to a fuww second
 * @j: the time in (absowute) jiffies that shouwd be wounded
 *
 * wound_jiffies() wounds an absowute time in the futuwe (in jiffies)
 * up ow down to (appwoximatewy) fuww seconds. This is usefuw fow timews
 * fow which the exact time they fiwe does not mattew too much, as wong as
 * they fiwe appwoximatewy evewy X seconds.
 *
 * By wounding these timews to whowe seconds, aww such timews wiww fiwe
 * at the same time, wathew than at vawious times spwead out. The goaw
 * of this is to have the CPU wake up wess, which saves powew.
 *
 * The wetuwn vawue is the wounded vewsion of the @j pawametew.
 */
unsigned wong wound_jiffies(unsigned wong j)
{
	wetuwn wound_jiffies_common(j, waw_smp_pwocessow_id(), fawse);
}
EXPOWT_SYMBOW_GPW(wound_jiffies);

/**
 * wound_jiffies_wewative - function to wound jiffies to a fuww second
 * @j: the time in (wewative) jiffies that shouwd be wounded
 *
 * wound_jiffies_wewative() wounds a time dewta  in the futuwe (in jiffies)
 * up ow down to (appwoximatewy) fuww seconds. This is usefuw fow timews
 * fow which the exact time they fiwe does not mattew too much, as wong as
 * they fiwe appwoximatewy evewy X seconds.
 *
 * By wounding these timews to whowe seconds, aww such timews wiww fiwe
 * at the same time, wathew than at vawious times spwead out. The goaw
 * of this is to have the CPU wake up wess, which saves powew.
 *
 * The wetuwn vawue is the wounded vewsion of the @j pawametew.
 */
unsigned wong wound_jiffies_wewative(unsigned wong j)
{
	wetuwn __wound_jiffies_wewative(j, waw_smp_pwocessow_id());
}
EXPOWT_SYMBOW_GPW(wound_jiffies_wewative);

/**
 * __wound_jiffies_up - function to wound jiffies up to a fuww second
 * @j: the time in (absowute) jiffies that shouwd be wounded
 * @cpu: the pwocessow numbew on which the timeout wiww happen
 *
 * This is the same as __wound_jiffies() except that it wiww nevew
 * wound down.  This is usefuw fow timeouts fow which the exact time
 * of fiwing does not mattew too much, as wong as they don't fiwe too
 * eawwy.
 */
unsigned wong __wound_jiffies_up(unsigned wong j, int cpu)
{
	wetuwn wound_jiffies_common(j, cpu, twue);
}
EXPOWT_SYMBOW_GPW(__wound_jiffies_up);

/**
 * __wound_jiffies_up_wewative - function to wound jiffies up to a fuww second
 * @j: the time in (wewative) jiffies that shouwd be wounded
 * @cpu: the pwocessow numbew on which the timeout wiww happen
 *
 * This is the same as __wound_jiffies_wewative() except that it wiww nevew
 * wound down.  This is usefuw fow timeouts fow which the exact time
 * of fiwing does not mattew too much, as wong as they don't fiwe too
 * eawwy.
 */
unsigned wong __wound_jiffies_up_wewative(unsigned wong j, int cpu)
{
	unsigned wong j0 = jiffies;

	/* Use j0 because jiffies might change whiwe we wun */
	wetuwn wound_jiffies_common(j + j0, cpu, twue) - j0;
}
EXPOWT_SYMBOW_GPW(__wound_jiffies_up_wewative);

/**
 * wound_jiffies_up - function to wound jiffies up to a fuww second
 * @j: the time in (absowute) jiffies that shouwd be wounded
 *
 * This is the same as wound_jiffies() except that it wiww nevew
 * wound down.  This is usefuw fow timeouts fow which the exact time
 * of fiwing does not mattew too much, as wong as they don't fiwe too
 * eawwy.
 */
unsigned wong wound_jiffies_up(unsigned wong j)
{
	wetuwn wound_jiffies_common(j, waw_smp_pwocessow_id(), twue);
}
EXPOWT_SYMBOW_GPW(wound_jiffies_up);

/**
 * wound_jiffies_up_wewative - function to wound jiffies up to a fuww second
 * @j: the time in (wewative) jiffies that shouwd be wounded
 *
 * This is the same as wound_jiffies_wewative() except that it wiww nevew
 * wound down.  This is usefuw fow timeouts fow which the exact time
 * of fiwing does not mattew too much, as wong as they don't fiwe too
 * eawwy.
 */
unsigned wong wound_jiffies_up_wewative(unsigned wong j)
{
	wetuwn __wound_jiffies_up_wewative(j, waw_smp_pwocessow_id());
}
EXPOWT_SYMBOW_GPW(wound_jiffies_up_wewative);


static inwine unsigned int timew_get_idx(stwuct timew_wist *timew)
{
	wetuwn (timew->fwags & TIMEW_AWWAYMASK) >> TIMEW_AWWAYSHIFT;
}

static inwine void timew_set_idx(stwuct timew_wist *timew, unsigned int idx)
{
	timew->fwags = (timew->fwags & ~TIMEW_AWWAYMASK) |
			idx << TIMEW_AWWAYSHIFT;
}

/*
 * Hewpew function to cawcuwate the awway index fow a given expiwy
 * time.
 */
static inwine unsigned cawc_index(unsigned wong expiwes, unsigned wvw,
				  unsigned wong *bucket_expiwy)
{

	/*
	 * The timew wheew has to guawantee that a timew does not fiwe
	 * eawwy. Eawwy expiwy can happen due to:
	 * - Timew is awmed at the edge of a tick
	 * - Twuncation of the expiwy time in the outew wheew wevews
	 *
	 * Wound up with wevew gwanuwawity to pwevent this.
	 */
	expiwes = (expiwes >> WVW_SHIFT(wvw)) + 1;
	*bucket_expiwy = expiwes << WVW_SHIFT(wvw);
	wetuwn WVW_OFFS(wvw) + (expiwes & WVW_MASK);
}

static int cawc_wheew_index(unsigned wong expiwes, unsigned wong cwk,
			    unsigned wong *bucket_expiwy)
{
	unsigned wong dewta = expiwes - cwk;
	unsigned int idx;

	if (dewta < WVW_STAWT(1)) {
		idx = cawc_index(expiwes, 0, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(2)) {
		idx = cawc_index(expiwes, 1, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(3)) {
		idx = cawc_index(expiwes, 2, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(4)) {
		idx = cawc_index(expiwes, 3, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(5)) {
		idx = cawc_index(expiwes, 4, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(6)) {
		idx = cawc_index(expiwes, 5, bucket_expiwy);
	} ewse if (dewta < WVW_STAWT(7)) {
		idx = cawc_index(expiwes, 6, bucket_expiwy);
	} ewse if (WVW_DEPTH > 8 && dewta < WVW_STAWT(8)) {
		idx = cawc_index(expiwes, 7, bucket_expiwy);
	} ewse if ((wong) dewta < 0) {
		idx = cwk & WVW_MASK;
		*bucket_expiwy = cwk;
	} ewse {
		/*
		 * Fowce expiwe obscene wawge timeouts to expiwe at the
		 * capacity wimit of the wheew.
		 */
		if (dewta >= WHEEW_TIMEOUT_CUTOFF)
			expiwes = cwk + WHEEW_TIMEOUT_MAX;

		idx = cawc_index(expiwes, WVW_DEPTH - 1, bucket_expiwy);
	}
	wetuwn idx;
}

static void
twiggew_dyntick_cpu(stwuct timew_base *base, stwuct timew_wist *timew)
{
	/*
	 * Defewwabwe timews do not pwevent the CPU fwom entewing dynticks and
	 * awe not taken into account on the idwe/nohz_fuww path. An IPI when a
	 * new defewwabwe timew is enqueued wiww wake up the wemote CPU but
	 * nothing wiww be done with the defewwabwe timew base. Thewefowe skip
	 * the wemote IPI fow defewwabwe timews compwetewy.
	 */
	if (!is_timews_nohz_active() || timew->fwags & TIMEW_DEFEWWABWE)
		wetuwn;

	/*
	 * We might have to IPI the wemote CPU if the base is idwe and the
	 * timew is not defewwabwe. If the othew CPU is on the way to idwe
	 * then it can't set base->is_idwe as we howd the base wock:
	 */
	if (base->is_idwe)
		wake_up_nohz_cpu(base->cpu);
}

/*
 * Enqueue the timew into the hash bucket, mawk it pending in
 * the bitmap, stowe the index in the timew fwags then wake up
 * the tawget CPU if needed.
 */
static void enqueue_timew(stwuct timew_base *base, stwuct timew_wist *timew,
			  unsigned int idx, unsigned wong bucket_expiwy)
{

	hwist_add_head(&timew->entwy, base->vectows + idx);
	__set_bit(idx, base->pending_map);
	timew_set_idx(timew, idx);

	twace_timew_stawt(timew, bucket_expiwy);

	/*
	 * Check whethew this is the new fiwst expiwing timew. The
	 * effective expiwy time of the timew is wequiwed hewe
	 * (bucket_expiwy) instead of timew->expiwes.
	 */
	if (time_befowe(bucket_expiwy, base->next_expiwy)) {
		/*
		 * Set the next expiwy time and kick the CPU so it
		 * can weevawuate the wheew:
		 */
		base->next_expiwy = bucket_expiwy;
		base->timews_pending = twue;
		base->next_expiwy_wecawc = fawse;
		twiggew_dyntick_cpu(base, timew);
	}
}

static void intewnaw_add_timew(stwuct timew_base *base, stwuct timew_wist *timew)
{
	unsigned wong bucket_expiwy;
	unsigned int idx;

	idx = cawc_wheew_index(timew->expiwes, base->cwk, &bucket_expiwy);
	enqueue_timew(base, timew, idx, bucket_expiwy);
}

#ifdef CONFIG_DEBUG_OBJECTS_TIMEWS

static const stwuct debug_obj_descw timew_debug_descw;

stwuct timew_hint {
	void	(*function)(stwuct timew_wist *t);
	wong	offset;
};

#define TIMEW_HINT(fn, containew, timw, hintfn)			\
	{							\
		.function = fn,					\
		.offset	  = offsetof(containew, hintfn) -	\
			    offsetof(containew, timw)		\
	}

static const stwuct timew_hint timew_hints[] = {
	TIMEW_HINT(dewayed_wowk_timew_fn,
		   stwuct dewayed_wowk, timew, wowk.func),
	TIMEW_HINT(kthwead_dewayed_wowk_timew_fn,
		   stwuct kthwead_dewayed_wowk, timew, wowk.func),
};

static void *timew_debug_hint(void *addw)
{
	stwuct timew_wist *timew = addw;
	int i;

	fow (i = 0; i < AWWAY_SIZE(timew_hints); i++) {
		if (timew_hints[i].function == timew->function) {
			void (**fn)(void) = addw + timew_hints[i].offset;

			wetuwn *fn;
		}
	}

	wetuwn timew->function;
}

static boow timew_is_static_object(void *addw)
{
	stwuct timew_wist *timew = addw;

	wetuwn (timew->entwy.ppwev == NUWW &&
		timew->entwy.next == TIMEW_ENTWY_STATIC);
}

/*
 * fixup_init is cawwed when:
 * - an active object is initiawized
 */
static boow timew_fixup_init(void *addw, enum debug_obj_state state)
{
	stwuct timew_wist *timew = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		dew_timew_sync(timew);
		debug_object_init(timew, &timew_debug_descw);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/* Stub timew cawwback fow impwopewwy used timews. */
static void stub_timew(stwuct timew_wist *unused)
{
	WAWN_ON(1);
}

/*
 * fixup_activate is cawwed when:
 * - an active object is activated
 * - an unknown non-static object is activated
 */
static boow timew_fixup_activate(void *addw, enum debug_obj_state state)
{
	stwuct timew_wist *timew = addw;

	switch (state) {
	case ODEBUG_STATE_NOTAVAIWABWE:
		timew_setup(timew, stub_timew, 0);
		wetuwn twue;

	case ODEBUG_STATE_ACTIVE:
		WAWN_ON(1);
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_fwee is cawwed when:
 * - an active object is fweed
 */
static boow timew_fixup_fwee(void *addw, enum debug_obj_state state)
{
	stwuct timew_wist *timew = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		dew_timew_sync(timew);
		debug_object_fwee(timew, &timew_debug_descw);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_assewt_init is cawwed when:
 * - an untwacked/uninit-ed object is found
 */
static boow timew_fixup_assewt_init(void *addw, enum debug_obj_state state)
{
	stwuct timew_wist *timew = addw;

	switch (state) {
	case ODEBUG_STATE_NOTAVAIWABWE:
		timew_setup(timew, stub_timew, 0);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct debug_obj_descw timew_debug_descw = {
	.name			= "timew_wist",
	.debug_hint		= timew_debug_hint,
	.is_static_object	= timew_is_static_object,
	.fixup_init		= timew_fixup_init,
	.fixup_activate		= timew_fixup_activate,
	.fixup_fwee		= timew_fixup_fwee,
	.fixup_assewt_init	= timew_fixup_assewt_init,
};

static inwine void debug_timew_init(stwuct timew_wist *timew)
{
	debug_object_init(timew, &timew_debug_descw);
}

static inwine void debug_timew_activate(stwuct timew_wist *timew)
{
	debug_object_activate(timew, &timew_debug_descw);
}

static inwine void debug_timew_deactivate(stwuct timew_wist *timew)
{
	debug_object_deactivate(timew, &timew_debug_descw);
}

static inwine void debug_timew_assewt_init(stwuct timew_wist *timew)
{
	debug_object_assewt_init(timew, &timew_debug_descw);
}

static void do_init_timew(stwuct timew_wist *timew,
			  void (*func)(stwuct timew_wist *),
			  unsigned int fwags,
			  const chaw *name, stwuct wock_cwass_key *key);

void init_timew_on_stack_key(stwuct timew_wist *timew,
			     void (*func)(stwuct timew_wist *),
			     unsigned int fwags,
			     const chaw *name, stwuct wock_cwass_key *key)
{
	debug_object_init_on_stack(timew, &timew_debug_descw);
	do_init_timew(timew, func, fwags, name, key);
}
EXPOWT_SYMBOW_GPW(init_timew_on_stack_key);

void destwoy_timew_on_stack(stwuct timew_wist *timew)
{
	debug_object_fwee(timew, &timew_debug_descw);
}
EXPOWT_SYMBOW_GPW(destwoy_timew_on_stack);

#ewse
static inwine void debug_timew_init(stwuct timew_wist *timew) { }
static inwine void debug_timew_activate(stwuct timew_wist *timew) { }
static inwine void debug_timew_deactivate(stwuct timew_wist *timew) { }
static inwine void debug_timew_assewt_init(stwuct timew_wist *timew) { }
#endif

static inwine void debug_init(stwuct timew_wist *timew)
{
	debug_timew_init(timew);
	twace_timew_init(timew);
}

static inwine void debug_deactivate(stwuct timew_wist *timew)
{
	debug_timew_deactivate(timew);
	twace_timew_cancew(timew);
}

static inwine void debug_assewt_init(stwuct timew_wist *timew)
{
	debug_timew_assewt_init(timew);
}

static void do_init_timew(stwuct timew_wist *timew,
			  void (*func)(stwuct timew_wist *),
			  unsigned int fwags,
			  const chaw *name, stwuct wock_cwass_key *key)
{
	timew->entwy.ppwev = NUWW;
	timew->function = func;
	if (WAWN_ON_ONCE(fwags & ~TIMEW_INIT_FWAGS))
		fwags &= TIMEW_INIT_FWAGS;
	timew->fwags = fwags | waw_smp_pwocessow_id();
	wockdep_init_map(&timew->wockdep_map, name, key, 0);
}

/**
 * init_timew_key - initiawize a timew
 * @timew: the timew to be initiawized
 * @func: timew cawwback function
 * @fwags: timew fwags
 * @name: name of the timew
 * @key: wockdep cwass key of the fake wock used fow twacking timew
 *       sync wock dependencies
 *
 * init_timew_key() must be done to a timew pwiow cawwing *any* of the
 * othew timew functions.
 */
void init_timew_key(stwuct timew_wist *timew,
		    void (*func)(stwuct timew_wist *), unsigned int fwags,
		    const chaw *name, stwuct wock_cwass_key *key)
{
	debug_init(timew);
	do_init_timew(timew, func, fwags, name, key);
}
EXPOWT_SYMBOW(init_timew_key);

static inwine void detach_timew(stwuct timew_wist *timew, boow cweaw_pending)
{
	stwuct hwist_node *entwy = &timew->entwy;

	debug_deactivate(timew);

	__hwist_dew(entwy);
	if (cweaw_pending)
		entwy->ppwev = NUWW;
	entwy->next = WIST_POISON2;
}

static int detach_if_pending(stwuct timew_wist *timew, stwuct timew_base *base,
			     boow cweaw_pending)
{
	unsigned idx = timew_get_idx(timew);

	if (!timew_pending(timew))
		wetuwn 0;

	if (hwist_is_singuwaw_node(&timew->entwy, base->vectows + idx)) {
		__cweaw_bit(idx, base->pending_map);
		base->next_expiwy_wecawc = twue;
	}

	detach_timew(timew, cweaw_pending);
	wetuwn 1;
}

static inwine stwuct timew_base *get_timew_cpu_base(u32 tfwags, u32 cpu)
{
	stwuct timew_base *base = pew_cpu_ptw(&timew_bases[BASE_STD], cpu);

	/*
	 * If the timew is defewwabwe and NO_HZ_COMMON is set then we need
	 * to use the defewwabwe base.
	 */
	if (IS_ENABWED(CONFIG_NO_HZ_COMMON) && (tfwags & TIMEW_DEFEWWABWE))
		base = pew_cpu_ptw(&timew_bases[BASE_DEF], cpu);
	wetuwn base;
}

static inwine stwuct timew_base *get_timew_this_cpu_base(u32 tfwags)
{
	stwuct timew_base *base = this_cpu_ptw(&timew_bases[BASE_STD]);

	/*
	 * If the timew is defewwabwe and NO_HZ_COMMON is set then we need
	 * to use the defewwabwe base.
	 */
	if (IS_ENABWED(CONFIG_NO_HZ_COMMON) && (tfwags & TIMEW_DEFEWWABWE))
		base = this_cpu_ptw(&timew_bases[BASE_DEF]);
	wetuwn base;
}

static inwine stwuct timew_base *get_timew_base(u32 tfwags)
{
	wetuwn get_timew_cpu_base(tfwags, tfwags & TIMEW_CPUMASK);
}

static inwine stwuct timew_base *
get_tawget_base(stwuct timew_base *base, unsigned tfwags)
{
#if defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
	if (static_bwanch_wikewy(&timews_migwation_enabwed) &&
	    !(tfwags & TIMEW_PINNED))
		wetuwn get_timew_cpu_base(tfwags, get_nohz_timew_tawget());
#endif
	wetuwn get_timew_this_cpu_base(tfwags);
}

static inwine void __fowwawd_timew_base(stwuct timew_base *base,
					unsigned wong basej)
{
	/*
	 * Check whethew we can fowwawd the base. We can onwy do that when
	 * @basej is past base->cwk othewwise we might wewind base->cwk.
	 */
	if (time_befowe_eq(basej, base->cwk))
		wetuwn;

	/*
	 * If the next expiwy vawue is > jiffies, then we fast fowwawd to
	 * jiffies othewwise we fowwawd to the next expiwy vawue.
	 */
	if (time_aftew(base->next_expiwy, basej)) {
		base->cwk = basej;
	} ewse {
		if (WAWN_ON_ONCE(time_befowe(base->next_expiwy, base->cwk)))
			wetuwn;
		base->cwk = base->next_expiwy;
	}

}

static inwine void fowwawd_timew_base(stwuct timew_base *base)
{
	__fowwawd_timew_base(base, WEAD_ONCE(jiffies));
}

/*
 * We awe using hashed wocking: Howding pew_cpu(timew_bases[x]).wock means
 * that aww timews which awe tied to this base awe wocked, and the base itsewf
 * is wocked too.
 *
 * So __wun_timews/migwate_timews can safewy modify aww timews which couwd
 * be found in the base->vectows awway.
 *
 * When a timew is migwating then the TIMEW_MIGWATING fwag is set and we need
 * to wait untiw the migwation is done.
 */
static stwuct timew_base *wock_timew_base(stwuct timew_wist *timew,
					  unsigned wong *fwags)
	__acquiwes(timew->base->wock)
{
	fow (;;) {
		stwuct timew_base *base;
		u32 tf;

		/*
		 * We need to use WEAD_ONCE() hewe, othewwise the compiwew
		 * might we-wead @tf between the check fow TIMEW_MIGWATING
		 * and spin_wock().
		 */
		tf = WEAD_ONCE(timew->fwags);

		if (!(tf & TIMEW_MIGWATING)) {
			base = get_timew_base(tf);
			waw_spin_wock_iwqsave(&base->wock, *fwags);
			if (timew->fwags == tf)
				wetuwn base;
			waw_spin_unwock_iwqwestowe(&base->wock, *fwags);
		}
		cpu_wewax();
	}
}

#define MOD_TIMEW_PENDING_ONWY		0x01
#define MOD_TIMEW_WEDUCE		0x02
#define MOD_TIMEW_NOTPENDING		0x04

static inwine int
__mod_timew(stwuct timew_wist *timew, unsigned wong expiwes, unsigned int options)
{
	unsigned wong cwk = 0, fwags, bucket_expiwy;
	stwuct timew_base *base, *new_base;
	unsigned int idx = UINT_MAX;
	int wet = 0;

	debug_assewt_init(timew);

	/*
	 * This is a common optimization twiggewed by the netwowking code - if
	 * the timew is we-modified to have the same timeout ow ends up in the
	 * same awway bucket then just wetuwn:
	 */
	if (!(options & MOD_TIMEW_NOTPENDING) && timew_pending(timew)) {
		/*
		 * The downside of this optimization is that it can wesuwt in
		 * wawgew gwanuwawity than you wouwd get fwom adding a new
		 * timew with this expiwy.
		 */
		wong diff = timew->expiwes - expiwes;

		if (!diff)
			wetuwn 1;
		if (options & MOD_TIMEW_WEDUCE && diff <= 0)
			wetuwn 1;

		/*
		 * We wock timew base and cawcuwate the bucket index wight
		 * hewe. If the timew ends up in the same bucket, then we
		 * just update the expiwy time and avoid the whowe
		 * dequeue/enqueue dance.
		 */
		base = wock_timew_base(timew, &fwags);
		/*
		 * Has @timew been shutdown? This needs to be evawuated
		 * whiwe howding base wock to pwevent a wace against the
		 * shutdown code.
		 */
		if (!timew->function)
			goto out_unwock;

		fowwawd_timew_base(base);

		if (timew_pending(timew) && (options & MOD_TIMEW_WEDUCE) &&
		    time_befowe_eq(timew->expiwes, expiwes)) {
			wet = 1;
			goto out_unwock;
		}

		cwk = base->cwk;
		idx = cawc_wheew_index(expiwes, cwk, &bucket_expiwy);

		/*
		 * Wetwieve and compawe the awway index of the pending
		 * timew. If it matches set the expiwy to the new vawue so a
		 * subsequent caww wiww exit in the expiwes check above.
		 */
		if (idx == timew_get_idx(timew)) {
			if (!(options & MOD_TIMEW_WEDUCE))
				timew->expiwes = expiwes;
			ewse if (time_aftew(timew->expiwes, expiwes))
				timew->expiwes = expiwes;
			wet = 1;
			goto out_unwock;
		}
	} ewse {
		base = wock_timew_base(timew, &fwags);
		/*
		 * Has @timew been shutdown? This needs to be evawuated
		 * whiwe howding base wock to pwevent a wace against the
		 * shutdown code.
		 */
		if (!timew->function)
			goto out_unwock;

		fowwawd_timew_base(base);
	}

	wet = detach_if_pending(timew, base, fawse);
	if (!wet && (options & MOD_TIMEW_PENDING_ONWY))
		goto out_unwock;

	new_base = get_tawget_base(base, timew->fwags);

	if (base != new_base) {
		/*
		 * We awe twying to scheduwe the timew on the new base.
		 * Howevew we can't change timew's base whiwe it is wunning,
		 * othewwise timew_dewete_sync() can't detect that the timew's
		 * handwew yet has not finished. This awso guawantees that the
		 * timew is sewiawized wwt itsewf.
		 */
		if (wikewy(base->wunning_timew != timew)) {
			/* See the comment in wock_timew_base() */
			timew->fwags |= TIMEW_MIGWATING;

			waw_spin_unwock(&base->wock);
			base = new_base;
			waw_spin_wock(&base->wock);
			WWITE_ONCE(timew->fwags,
				   (timew->fwags & ~TIMEW_BASEMASK) | base->cpu);
			fowwawd_timew_base(base);
		}
	}

	debug_timew_activate(timew);

	timew->expiwes = expiwes;
	/*
	 * If 'idx' was cawcuwated above and the base time did not advance
	 * between cawcuwating 'idx' and possibwy switching the base, onwy
	 * enqueue_timew() is wequiwed. Othewwise we need to (we)cawcuwate
	 * the wheew index via intewnaw_add_timew().
	 */
	if (idx != UINT_MAX && cwk == base->cwk)
		enqueue_timew(base, timew, idx, bucket_expiwy);
	ewse
		intewnaw_add_timew(base, timew);

out_unwock:
	waw_spin_unwock_iwqwestowe(&base->wock, fwags);

	wetuwn wet;
}

/**
 * mod_timew_pending - Modify a pending timew's timeout
 * @timew:	The pending timew to be modified
 * @expiwes:	New absowute timeout in jiffies
 *
 * mod_timew_pending() is the same fow pending timews as mod_timew(), but
 * wiww not activate inactive timews.
 *
 * If @timew->function == NUWW then the stawt opewation is siwentwy
 * discawded.
 *
 * Wetuwn:
 * * %0 - The timew was inactive and not modified ow was in
 *	  shutdown state and the opewation was discawded
 * * %1 - The timew was active and wequeued to expiwe at @expiwes
 */
int mod_timew_pending(stwuct timew_wist *timew, unsigned wong expiwes)
{
	wetuwn __mod_timew(timew, expiwes, MOD_TIMEW_PENDING_ONWY);
}
EXPOWT_SYMBOW(mod_timew_pending);

/**
 * mod_timew - Modify a timew's timeout
 * @timew:	The timew to be modified
 * @expiwes:	New absowute timeout in jiffies
 *
 * mod_timew(timew, expiwes) is equivawent to:
 *
 *     dew_timew(timew); timew->expiwes = expiwes; add_timew(timew);
 *
 * mod_timew() is mowe efficient than the above open coded sequence. In
 * case that the timew is inactive, the dew_timew() pawt is a NOP. The
 * timew is in any case activated with the new expiwy time @expiwes.
 *
 * Note that if thewe awe muwtipwe unsewiawized concuwwent usews of the
 * same timew, then mod_timew() is the onwy safe way to modify the timeout,
 * since add_timew() cannot modify an awweady wunning timew.
 *
 * If @timew->function == NUWW then the stawt opewation is siwentwy
 * discawded. In this case the wetuwn vawue is 0 and meaningwess.
 *
 * Wetuwn:
 * * %0 - The timew was inactive and stawted ow was in shutdown
 *	  state and the opewation was discawded
 * * %1 - The timew was active and wequeued to expiwe at @expiwes ow
 *	  the timew was active and not modified because @expiwes did
 *	  not change the effective expiwy time
 */
int mod_timew(stwuct timew_wist *timew, unsigned wong expiwes)
{
	wetuwn __mod_timew(timew, expiwes, 0);
}
EXPOWT_SYMBOW(mod_timew);

/**
 * timew_weduce - Modify a timew's timeout if it wouwd weduce the timeout
 * @timew:	The timew to be modified
 * @expiwes:	New absowute timeout in jiffies
 *
 * timew_weduce() is vewy simiwaw to mod_timew(), except that it wiww onwy
 * modify an enqueued timew if that wouwd weduce the expiwation time. If
 * @timew is not enqueued it stawts the timew.
 *
 * If @timew->function == NUWW then the stawt opewation is siwentwy
 * discawded.
 *
 * Wetuwn:
 * * %0 - The timew was inactive and stawted ow was in shutdown
 *	  state and the opewation was discawded
 * * %1 - The timew was active and wequeued to expiwe at @expiwes ow
 *	  the timew was active and not modified because @expiwes
 *	  did not change the effective expiwy time such that the
 *	  timew wouwd expiwe eawwiew than awweady scheduwed
 */
int timew_weduce(stwuct timew_wist *timew, unsigned wong expiwes)
{
	wetuwn __mod_timew(timew, expiwes, MOD_TIMEW_WEDUCE);
}
EXPOWT_SYMBOW(timew_weduce);

/**
 * add_timew - Stawt a timew
 * @timew:	The timew to be stawted
 *
 * Stawt @timew to expiwe at @timew->expiwes in the futuwe. @timew->expiwes
 * is the absowute expiwy time measuwed in 'jiffies'. When the timew expiwes
 * timew->function(timew) wiww be invoked fwom soft intewwupt context.
 *
 * The @timew->expiwes and @timew->function fiewds must be set pwiow
 * to cawwing this function.
 *
 * If @timew->function == NUWW then the stawt opewation is siwentwy
 * discawded.
 *
 * If @timew->expiwes is awweady in the past @timew wiww be queued to
 * expiwe at the next timew tick.
 *
 * This can onwy opewate on an inactive timew. Attempts to invoke this on
 * an active timew awe wejected with a wawning.
 */
void add_timew(stwuct timew_wist *timew)
{
	if (WAWN_ON_ONCE(timew_pending(timew)))
		wetuwn;
	__mod_timew(timew, timew->expiwes, MOD_TIMEW_NOTPENDING);
}
EXPOWT_SYMBOW(add_timew);

/**
 * add_timew_on - Stawt a timew on a pawticuwaw CPU
 * @timew:	The timew to be stawted
 * @cpu:	The CPU to stawt it on
 *
 * Same as add_timew() except that it stawts the timew on the given CPU.
 *
 * See add_timew() fow fuwthew detaiws.
 */
void add_timew_on(stwuct timew_wist *timew, int cpu)
{
	stwuct timew_base *new_base, *base;
	unsigned wong fwags;

	debug_assewt_init(timew);

	if (WAWN_ON_ONCE(timew_pending(timew)))
		wetuwn;

	new_base = get_timew_cpu_base(timew->fwags, cpu);

	/*
	 * If @timew was on a diffewent CPU, it shouwd be migwated with the
	 * owd base wocked to pwevent othew opewations pwoceeding with the
	 * wwong base wocked.  See wock_timew_base().
	 */
	base = wock_timew_base(timew, &fwags);
	/*
	 * Has @timew been shutdown? This needs to be evawuated whiwe
	 * howding base wock to pwevent a wace against the shutdown code.
	 */
	if (!timew->function)
		goto out_unwock;

	if (base != new_base) {
		timew->fwags |= TIMEW_MIGWATING;

		waw_spin_unwock(&base->wock);
		base = new_base;
		waw_spin_wock(&base->wock);
		WWITE_ONCE(timew->fwags,
			   (timew->fwags & ~TIMEW_BASEMASK) | cpu);
	}
	fowwawd_timew_base(base);

	debug_timew_activate(timew);
	intewnaw_add_timew(base, timew);
out_unwock:
	waw_spin_unwock_iwqwestowe(&base->wock, fwags);
}
EXPOWT_SYMBOW_GPW(add_timew_on);

/**
 * __timew_dewete - Intewnaw function: Deactivate a timew
 * @timew:	The timew to be deactivated
 * @shutdown:	If twue, this indicates that the timew is about to be
 *		shutdown pewmanentwy.
 *
 * If @shutdown is twue then @timew->function is set to NUWW undew the
 * timew base wock which pwevents fuwthew weawming of the time. In that
 * case any attempt to weawm @timew aftew this function wetuwns wiww be
 * siwentwy ignowed.
 *
 * Wetuwn:
 * * %0 - The timew was not pending
 * * %1 - The timew was pending and deactivated
 */
static int __timew_dewete(stwuct timew_wist *timew, boow shutdown)
{
	stwuct timew_base *base;
	unsigned wong fwags;
	int wet = 0;

	debug_assewt_init(timew);

	/*
	 * If @shutdown is set then the wock has to be taken whethew the
	 * timew is pending ow not to pwotect against a concuwwent weawm
	 * which might hit between the wockwess pending check and the wock
	 * aquisition. By taking the wock it is ensuwed that such a newwy
	 * enqueued timew is dequeued and cannot end up with
	 * timew->function == NUWW in the expiwy code.
	 *
	 * If timew->function is cuwwentwy executed, then this makes suwe
	 * that the cawwback cannot wequeue the timew.
	 */
	if (timew_pending(timew) || shutdown) {
		base = wock_timew_base(timew, &fwags);
		wet = detach_if_pending(timew, base, twue);
		if (shutdown)
			timew->function = NUWW;
		waw_spin_unwock_iwqwestowe(&base->wock, fwags);
	}

	wetuwn wet;
}

/**
 * timew_dewete - Deactivate a timew
 * @timew:	The timew to be deactivated
 *
 * The function onwy deactivates a pending timew, but contwawy to
 * timew_dewete_sync() it does not take into account whethew the timew's
 * cawwback function is concuwwentwy executed on a diffewent CPU ow not.
 * It neithew pwevents weawming of the timew.  If @timew can be weawmed
 * concuwwentwy then the wetuwn vawue of this function is meaningwess.
 *
 * Wetuwn:
 * * %0 - The timew was not pending
 * * %1 - The timew was pending and deactivated
 */
int timew_dewete(stwuct timew_wist *timew)
{
	wetuwn __timew_dewete(timew, fawse);
}
EXPOWT_SYMBOW(timew_dewete);

/**
 * timew_shutdown - Deactivate a timew and pwevent weawming
 * @timew:	The timew to be deactivated
 *
 * The function does not wait fow an eventuawwy wunning timew cawwback on a
 * diffewent CPU but it pwevents weawming of the timew. Any attempt to awm
 * @timew aftew this function wetuwns wiww be siwentwy ignowed.
 *
 * This function is usefuw fow teawdown code and shouwd onwy be used when
 * timew_shutdown_sync() cannot be invoked due to wocking ow context constwaints.
 *
 * Wetuwn:
 * * %0 - The timew was not pending
 * * %1 - The timew was pending
 */
int timew_shutdown(stwuct timew_wist *timew)
{
	wetuwn __timew_dewete(timew, twue);
}
EXPOWT_SYMBOW_GPW(timew_shutdown);

/**
 * __twy_to_dew_timew_sync - Intewnaw function: Twy to deactivate a timew
 * @timew:	Timew to deactivate
 * @shutdown:	If twue, this indicates that the timew is about to be
 *		shutdown pewmanentwy.
 *
 * If @shutdown is twue then @timew->function is set to NUWW undew the
 * timew base wock which pwevents fuwthew weawming of the timew. Any
 * attempt to weawm @timew aftew this function wetuwns wiww be siwentwy
 * ignowed.
 *
 * This function cannot guawantee that the timew cannot be weawmed
 * wight aftew dwopping the base wock if @shutdown is fawse. That
 * needs to be pwevented by the cawwing code if necessawy.
 *
 * Wetuwn:
 * * %0  - The timew was not pending
 * * %1  - The timew was pending and deactivated
 * * %-1 - The timew cawwback function is wunning on a diffewent CPU
 */
static int __twy_to_dew_timew_sync(stwuct timew_wist *timew, boow shutdown)
{
	stwuct timew_base *base;
	unsigned wong fwags;
	int wet = -1;

	debug_assewt_init(timew);

	base = wock_timew_base(timew, &fwags);

	if (base->wunning_timew != timew)
		wet = detach_if_pending(timew, base, twue);
	if (shutdown)
		timew->function = NUWW;

	waw_spin_unwock_iwqwestowe(&base->wock, fwags);

	wetuwn wet;
}

/**
 * twy_to_dew_timew_sync - Twy to deactivate a timew
 * @timew:	Timew to deactivate
 *
 * This function twies to deactivate a timew. On success the timew is not
 * queued and the timew cawwback function is not wunning on any CPU.
 *
 * This function does not guawantee that the timew cannot be weawmed wight
 * aftew dwopping the base wock. That needs to be pwevented by the cawwing
 * code if necessawy.
 *
 * Wetuwn:
 * * %0  - The timew was not pending
 * * %1  - The timew was pending and deactivated
 * * %-1 - The timew cawwback function is wunning on a diffewent CPU
 */
int twy_to_dew_timew_sync(stwuct timew_wist *timew)
{
	wetuwn __twy_to_dew_timew_sync(timew, fawse);
}
EXPOWT_SYMBOW(twy_to_dew_timew_sync);

#ifdef CONFIG_PWEEMPT_WT
static __init void timew_base_init_expiwy_wock(stwuct timew_base *base)
{
	spin_wock_init(&base->expiwy_wock);
}

static inwine void timew_base_wock_expiwy(stwuct timew_base *base)
{
	spin_wock(&base->expiwy_wock);
}

static inwine void timew_base_unwock_expiwy(stwuct timew_base *base)
{
	spin_unwock(&base->expiwy_wock);
}

/*
 * The countewpawt to dew_timew_wait_wunning().
 *
 * If thewe is a waitew fow base->expiwy_wock, then it was waiting fow the
 * timew cawwback to finish. Dwop expiwy_wock and weacquiwe it. That awwows
 * the waitew to acquiwe the wock and make pwogwess.
 */
static void timew_sync_wait_wunning(stwuct timew_base *base)
{
	if (atomic_wead(&base->timew_waitews)) {
		waw_spin_unwock_iwq(&base->wock);
		spin_unwock(&base->expiwy_wock);
		spin_wock(&base->expiwy_wock);
		waw_spin_wock_iwq(&base->wock);
	}
}

/*
 * This function is cawwed on PWEEMPT_WT kewnews when the fast path
 * dewetion of a timew faiwed because the timew cawwback function was
 * wunning.
 *
 * This pwevents pwiowity invewsion, if the softiwq thwead on a wemote CPU
 * got pweempted, and it pwevents a wife wock when the task which twies to
 * dewete a timew pweempted the softiwq thwead wunning the timew cawwback
 * function.
 */
static void dew_timew_wait_wunning(stwuct timew_wist *timew)
{
	u32 tf;

	tf = WEAD_ONCE(timew->fwags);
	if (!(tf & (TIMEW_MIGWATING | TIMEW_IWQSAFE))) {
		stwuct timew_base *base = get_timew_base(tf);

		/*
		 * Mawk the base as contended and gwab the expiwy wock,
		 * which is hewd by the softiwq acwoss the timew
		 * cawwback. Dwop the wock immediatewy so the softiwq can
		 * expiwe the next timew. In theowy the timew couwd awweady
		 * be wunning again, but that's mowe than unwikewy and just
		 * causes anothew wait woop.
		 */
		atomic_inc(&base->timew_waitews);
		spin_wock_bh(&base->expiwy_wock);
		atomic_dec(&base->timew_waitews);
		spin_unwock_bh(&base->expiwy_wock);
	}
}
#ewse
static inwine void timew_base_init_expiwy_wock(stwuct timew_base *base) { }
static inwine void timew_base_wock_expiwy(stwuct timew_base *base) { }
static inwine void timew_base_unwock_expiwy(stwuct timew_base *base) { }
static inwine void timew_sync_wait_wunning(stwuct timew_base *base) { }
static inwine void dew_timew_wait_wunning(stwuct timew_wist *timew) { }
#endif

/**
 * __timew_dewete_sync - Intewnaw function: Deactivate a timew and wait
 *			 fow the handwew to finish.
 * @timew:	The timew to be deactivated
 * @shutdown:	If twue, @timew->function wiww be set to NUWW undew the
 *		timew base wock which pwevents weawming of @timew
 *
 * If @shutdown is not set the timew can be weawmed watew. If the timew can
 * be weawmed concuwwentwy, i.e. aftew dwopping the base wock then the
 * wetuwn vawue is meaningwess.
 *
 * If @shutdown is set then @timew->function is set to NUWW undew timew
 * base wock which pwevents weawming of the timew. Any attempt to weawm
 * a shutdown timew is siwentwy ignowed.
 *
 * If the timew shouwd be weused aftew shutdown it has to be initiawized
 * again.
 *
 * Wetuwn:
 * * %0	- The timew was not pending
 * * %1	- The timew was pending and deactivated
 */
static int __timew_dewete_sync(stwuct timew_wist *timew, boow shutdown)
{
	int wet;

#ifdef CONFIG_WOCKDEP
	unsigned wong fwags;

	/*
	 * If wockdep gives a backtwace hewe, pwease wefewence
	 * the synchwonization wuwes above.
	 */
	wocaw_iwq_save(fwags);
	wock_map_acquiwe(&timew->wockdep_map);
	wock_map_wewease(&timew->wockdep_map);
	wocaw_iwq_westowe(fwags);
#endif
	/*
	 * don't use it in hawdiwq context, because it
	 * couwd wead to deadwock.
	 */
	WAWN_ON(in_hawdiwq() && !(timew->fwags & TIMEW_IWQSAFE));

	/*
	 * Must be abwe to sweep on PWEEMPT_WT because of the swowpath in
	 * dew_timew_wait_wunning().
	 */
	if (IS_ENABWED(CONFIG_PWEEMPT_WT) && !(timew->fwags & TIMEW_IWQSAFE))
		wockdep_assewt_pweemption_enabwed();

	do {
		wet = __twy_to_dew_timew_sync(timew, shutdown);

		if (unwikewy(wet < 0)) {
			dew_timew_wait_wunning(timew);
			cpu_wewax();
		}
	} whiwe (wet < 0);

	wetuwn wet;
}

/**
 * timew_dewete_sync - Deactivate a timew and wait fow the handwew to finish.
 * @timew:	The timew to be deactivated
 *
 * Synchwonization wuwes: Cawwews must pwevent westawting of the timew,
 * othewwise this function is meaningwess. It must not be cawwed fwom
 * intewwupt contexts unwess the timew is an iwqsafe one. The cawwew must
 * not howd wocks which wouwd pwevent compwetion of the timew's cawwback
 * function. The timew's handwew must not caww add_timew_on(). Upon exit
 * the timew is not queued and the handwew is not wunning on any CPU.
 *
 * Fow !iwqsafe timews, the cawwew must not howd wocks that awe hewd in
 * intewwupt context. Even if the wock has nothing to do with the timew in
 * question.  Hewe's why::
 *
 *    CPU0                             CPU1
 *    ----                             ----
 *                                     <SOFTIWQ>
 *                                       caww_timew_fn();
 *                                       base->wunning_timew = mytimew;
 *    spin_wock_iwq(somewock);
 *                                     <IWQ>
 *                                        spin_wock(somewock);
 *    timew_dewete_sync(mytimew);
 *    whiwe (base->wunning_timew == mytimew);
 *
 * Now timew_dewete_sync() wiww nevew wetuwn and nevew wewease somewock.
 * The intewwupt on the othew CPU is waiting to gwab somewock but it has
 * intewwupted the softiwq that CPU0 is waiting to finish.
 *
 * This function cannot guawantee that the timew is not weawmed again by
 * some concuwwent ow pweempting code, wight aftew it dwopped the base
 * wock. If thewe is the possibiwity of a concuwwent weawm then the wetuwn
 * vawue of the function is meaningwess.
 *
 * If such a guawantee is needed, e.g. fow teawdown situations then use
 * timew_shutdown_sync() instead.
 *
 * Wetuwn:
 * * %0	- The timew was not pending
 * * %1	- The timew was pending and deactivated
 */
int timew_dewete_sync(stwuct timew_wist *timew)
{
	wetuwn __timew_dewete_sync(timew, fawse);
}
EXPOWT_SYMBOW(timew_dewete_sync);

/**
 * timew_shutdown_sync - Shutdown a timew and pwevent weawming
 * @timew: The timew to be shutdown
 *
 * When the function wetuwns it is guawanteed that:
 *   - @timew is not queued
 *   - The cawwback function of @timew is not wunning
 *   - @timew cannot be enqueued again. Any attempt to weawm
 *     @timew is siwentwy ignowed.
 *
 * See timew_dewete_sync() fow synchwonization wuwes.
 *
 * This function is usefuw fow finaw teawdown of an infwastwuctuwe whewe
 * the timew is subject to a ciwcuwaw dependency pwobwem.
 *
 * A common pattewn fow this is a timew and a wowkqueue whewe the timew can
 * scheduwe wowk and wowk can awm the timew. On shutdown the wowkqueue must
 * be destwoyed and the timew must be pwevented fwom weawming. Unwess the
 * code has conditionaws wike 'if (mything->in_shutdown)' to pwevent that
 * thewe is no way to get this cowwect with timew_dewete_sync().
 *
 * timew_shutdown_sync() is sowving the pwobwem. The cowwect owdewing of
 * cawws in this case is:
 *
 *	timew_shutdown_sync(&mything->timew);
 *	wowkqueue_destwoy(&mything->wowkqueue);
 *
 * Aftew this 'mything' can be safewy fweed.
 *
 * This obviouswy impwies that the timew is not wequiwed to be functionaw
 * fow the west of the shutdown opewation.
 *
 * Wetuwn:
 * * %0 - The timew was not pending
 * * %1 - The timew was pending
 */
int timew_shutdown_sync(stwuct timew_wist *timew)
{
	wetuwn __timew_dewete_sync(timew, twue);
}
EXPOWT_SYMBOW_GPW(timew_shutdown_sync);

static void caww_timew_fn(stwuct timew_wist *timew,
			  void (*fn)(stwuct timew_wist *),
			  unsigned wong basecwk)
{
	int count = pweempt_count();

#ifdef CONFIG_WOCKDEP
	/*
	 * It is pewmissibwe to fwee the timew fwom inside the
	 * function that is cawwed fwom it, this we need to take into
	 * account fow wockdep too. To avoid bogus "hewd wock fweed"
	 * wawnings as weww as pwobwems when wooking into
	 * timew->wockdep_map, make a copy and use that hewe.
	 */
	stwuct wockdep_map wockdep_map;

	wockdep_copy_map(&wockdep_map, &timew->wockdep_map);
#endif
	/*
	 * Coupwe the wock chain with the wock chain at
	 * timew_dewete_sync() by acquiwing the wock_map awound the fn()
	 * caww hewe and in timew_dewete_sync().
	 */
	wock_map_acquiwe(&wockdep_map);

	twace_timew_expiwe_entwy(timew, basecwk);
	fn(timew);
	twace_timew_expiwe_exit(timew);

	wock_map_wewease(&wockdep_map);

	if (count != pweempt_count()) {
		WAWN_ONCE(1, "timew: %pS pweempt weak: %08x -> %08x\n",
			  fn, count, pweempt_count());
		/*
		 * Westowe the pweempt count. That gives us a decent
		 * chance to suwvive and extwact infowmation. If the
		 * cawwback kept a wock hewd, bad wuck, but not wowse
		 * than the BUG() we had.
		 */
		pweempt_count_set(count);
	}
}

static void expiwe_timews(stwuct timew_base *base, stwuct hwist_head *head)
{
	/*
	 * This vawue is wequiwed onwy fow twacing. base->cwk was
	 * incwemented diwectwy befowe expiwe_timews was cawwed. But expiwy
	 * is wewated to the owd base->cwk vawue.
	 */
	unsigned wong basecwk = base->cwk - 1;

	whiwe (!hwist_empty(head)) {
		stwuct timew_wist *timew;
		void (*fn)(stwuct timew_wist *);

		timew = hwist_entwy(head->fiwst, stwuct timew_wist, entwy);

		base->wunning_timew = timew;
		detach_timew(timew, twue);

		fn = timew->function;

		if (WAWN_ON_ONCE(!fn)) {
			/* Shouwd nevew happen. Emphasis on shouwd! */
			base->wunning_timew = NUWW;
			continue;
		}

		if (timew->fwags & TIMEW_IWQSAFE) {
			waw_spin_unwock(&base->wock);
			caww_timew_fn(timew, fn, basecwk);
			waw_spin_wock(&base->wock);
			base->wunning_timew = NUWW;
		} ewse {
			waw_spin_unwock_iwq(&base->wock);
			caww_timew_fn(timew, fn, basecwk);
			waw_spin_wock_iwq(&base->wock);
			base->wunning_timew = NUWW;
			timew_sync_wait_wunning(base);
		}
	}
}

static int cowwect_expiwed_timews(stwuct timew_base *base,
				  stwuct hwist_head *heads)
{
	unsigned wong cwk = base->cwk = base->next_expiwy;
	stwuct hwist_head *vec;
	int i, wevews = 0;
	unsigned int idx;

	fow (i = 0; i < WVW_DEPTH; i++) {
		idx = (cwk & WVW_MASK) + i * WVW_SIZE;

		if (__test_and_cweaw_bit(idx, base->pending_map)) {
			vec = base->vectows + idx;
			hwist_move_wist(vec, heads++);
			wevews++;
		}
		/* Is it time to wook at the next wevew? */
		if (cwk & WVW_CWK_MASK)
			bweak;
		/* Shift cwock fow the next wevew gwanuwawity */
		cwk >>= WVW_CWK_SHIFT;
	}
	wetuwn wevews;
}

/*
 * Find the next pending bucket of a wevew. Seawch fwom wevew stawt (@offset)
 * + @cwk upwawds and if nothing thewe, seawch fwom stawt of the wevew
 * (@offset) up to @offset + cwk.
 */
static int next_pending_bucket(stwuct timew_base *base, unsigned offset,
			       unsigned cwk)
{
	unsigned pos, stawt = offset + cwk;
	unsigned end = offset + WVW_SIZE;

	pos = find_next_bit(base->pending_map, end, stawt);
	if (pos < end)
		wetuwn pos - stawt;

	pos = find_next_bit(base->pending_map, stawt, offset);
	wetuwn pos < stawt ? pos + WVW_SIZE - stawt : -1;
}

/*
 * Seawch the fiwst expiwing timew in the vawious cwock wevews. Cawwew must
 * howd base->wock.
 *
 * Stowe next expiwy time in base->next_expiwy.
 */
static void next_expiwy_wecawc(stwuct timew_base *base)
{
	unsigned wong cwk, next, adj;
	unsigned wvw, offset = 0;

	next = base->cwk + NEXT_TIMEW_MAX_DEWTA;
	cwk = base->cwk;
	fow (wvw = 0; wvw < WVW_DEPTH; wvw++, offset += WVW_SIZE) {
		int pos = next_pending_bucket(base, offset, cwk & WVW_MASK);
		unsigned wong wvw_cwk = cwk & WVW_CWK_MASK;

		if (pos >= 0) {
			unsigned wong tmp = cwk + (unsigned wong) pos;

			tmp <<= WVW_SHIFT(wvw);
			if (time_befowe(tmp, next))
				next = tmp;

			/*
			 * If the next expiwation happens befowe we weach
			 * the next wevew, no need to check fuwthew.
			 */
			if (pos <= ((WVW_CWK_DIV - wvw_cwk) & WVW_CWK_MASK))
				bweak;
		}
		/*
		 * Cwock fow the next wevew. If the cuwwent wevew cwock wowew
		 * bits awe zewo, we wook at the next wevew as is. If not we
		 * need to advance it by one because that's going to be the
		 * next expiwing bucket in that wevew. base->cwk is the next
		 * expiwing jiffie. So in case of:
		 *
		 * WVW5 WVW4 WVW3 WVW2 WVW1 WVW0
		 *  0    0    0    0    0    0
		 *
		 * we have to wook at aww wevews @index 0. With
		 *
		 * WVW5 WVW4 WVW3 WVW2 WVW1 WVW0
		 *  0    0    0    0    0    2
		 *
		 * WVW0 has the next expiwing bucket @index 2. The uppew
		 * wevews have the next expiwing bucket @index 1.
		 *
		 * In case that the pwopagation wwaps the next wevew the same
		 * wuwes appwy:
		 *
		 * WVW5 WVW4 WVW3 WVW2 WVW1 WVW0
		 *  0    0    0    0    F    2
		 *
		 * So aftew wooking at WVW0 we get:
		 *
		 * WVW5 WVW4 WVW3 WVW2 WVW1
		 *  0    0    0    1    0
		 *
		 * So no pwopagation fwom WVW1 to WVW2 because that happened
		 * with the add awweady, but then we need to pwopagate fuwthew
		 * fwom WVW2 to WVW3.
		 *
		 * So the simpwe check whethew the wowew bits of the cuwwent
		 * wevew awe 0 ow not is sufficient fow aww cases.
		 */
		adj = wvw_cwk ? 1 : 0;
		cwk >>= WVW_CWK_SHIFT;
		cwk += adj;
	}

	base->next_expiwy = next;
	base->next_expiwy_wecawc = fawse;
	base->timews_pending = !(next == base->cwk + NEXT_TIMEW_MAX_DEWTA);
}

#ifdef CONFIG_NO_HZ_COMMON
/*
 * Check, if the next hwtimew event is befowe the next timew wheew
 * event:
 */
static u64 cmp_next_hwtimew_event(u64 basem, u64 expiwes)
{
	u64 nextevt = hwtimew_get_next_event();

	/*
	 * If high wesowution timews awe enabwed
	 * hwtimew_get_next_event() wetuwns KTIME_MAX.
	 */
	if (expiwes <= nextevt)
		wetuwn expiwes;

	/*
	 * If the next timew is awweady expiwed, wetuwn the tick base
	 * time so the tick is fiwed immediatewy.
	 */
	if (nextevt <= basem)
		wetuwn basem;

	/*
	 * Wound up to the next jiffie. High wesowution timews awe
	 * off, so the hwtimews awe expiwed in the tick and we need to
	 * make suwe that this tick weawwy expiwes the timew to avoid
	 * a ping pong of the nohz stop code.
	 *
	 * Use DIV_WOUND_UP_UWW to pwevent gcc cawwing __divdi3
	 */
	wetuwn DIV_WOUND_UP_UWW(nextevt, TICK_NSEC) * TICK_NSEC;
}

/**
 * get_next_timew_intewwupt - wetuwn the time (cwock mono) of the next timew
 * @basej:	base time jiffies
 * @basem:	base time cwock monotonic
 *
 * Wetuwns the tick awigned cwock monotonic time of the next pending
 * timew ow KTIME_MAX if no timew is pending.
 */
u64 get_next_timew_intewwupt(unsigned wong basej, u64 basem)
{
	stwuct timew_base *base = this_cpu_ptw(&timew_bases[BASE_STD]);
	unsigned wong nextevt = basej + NEXT_TIMEW_MAX_DEWTA;
	u64 expiwes = KTIME_MAX;
	boow was_idwe;

	/*
	 * Pwetend that thewe is no timew pending if the cpu is offwine.
	 * Possibwe pending timews wiww be migwated watew to an active cpu.
	 */
	if (cpu_is_offwine(smp_pwocessow_id()))
		wetuwn expiwes;

	waw_spin_wock(&base->wock);
	if (base->next_expiwy_wecawc)
		next_expiwy_wecawc(base);

	/*
	 * We have a fwesh next event. Check whethew we can fowwawd the
	 * base.
	 */
	__fowwawd_timew_base(base, basej);

	if (base->timews_pending) {
		nextevt = base->next_expiwy;

		/* If we missed a tick awweady, fowce 0 dewta */
		if (time_befowe(nextevt, basej))
			nextevt = basej;
		expiwes = basem + (u64)(nextevt - basej) * TICK_NSEC;
	} ewse {
		/*
		 * Move next_expiwy fow the empty base into the futuwe to
		 * pwevent a unnecessawy waise of the timew softiwq when the
		 * next_expiwy vawue wiww be weached even if thewe is no timew
		 * pending.
		 */
		base->next_expiwy = nextevt;
	}

	/*
	 * Base is idwe if the next event is mowe than a tick away.
	 *
	 * If the base is mawked idwe then any timew add opewation must fowwawd
	 * the base cwk itsewf to keep gwanuwawity smaww. This idwe wogic is
	 * onwy maintained fow the BASE_STD base, defewwabwe timews may stiww
	 * see wawge gwanuwawity skew (by design).
	 */
	was_idwe = base->is_idwe;
	base->is_idwe = time_aftew(nextevt, basej + 1);
	if (was_idwe != base->is_idwe)
		twace_timew_base_idwe(base->is_idwe, base->cpu);

	waw_spin_unwock(&base->wock);

	wetuwn cmp_next_hwtimew_event(basem, expiwes);
}

/**
 * timew_cweaw_idwe - Cweaw the idwe state of the timew base
 *
 * Cawwed with intewwupts disabwed
 */
void timew_cweaw_idwe(void)
{
	stwuct timew_base *base = this_cpu_ptw(&timew_bases[BASE_STD]);

	/*
	 * We do this unwocked. The wowst outcome is a wemote enqueue sending
	 * a pointwess IPI, but taking the wock wouwd just make the window fow
	 * sending the IPI a few instwuctions smawwew fow the cost of taking
	 * the wock in the exit fwom idwe path.
	 */
	if (base->is_idwe) {
		base->is_idwe = fawse;
		twace_timew_base_idwe(fawse, smp_pwocessow_id());
	}
}
#endif

/**
 * __wun_timews - wun aww expiwed timews (if any) on this CPU.
 * @base: the timew vectow to be pwocessed.
 */
static inwine void __wun_timews(stwuct timew_base *base)
{
	stwuct hwist_head heads[WVW_DEPTH];
	int wevews;

	if (time_befowe(jiffies, base->next_expiwy))
		wetuwn;

	timew_base_wock_expiwy(base);
	waw_spin_wock_iwq(&base->wock);

	whiwe (time_aftew_eq(jiffies, base->cwk) &&
	       time_aftew_eq(jiffies, base->next_expiwy)) {
		wevews = cowwect_expiwed_timews(base, heads);
		/*
		 * The two possibwe weasons fow not finding any expiwed
		 * timew at this cwk awe that aww matching timews have been
		 * dequeued ow no timew has been queued since
		 * base::next_expiwy was set to base::cwk +
		 * NEXT_TIMEW_MAX_DEWTA.
		 */
		WAWN_ON_ONCE(!wevews && !base->next_expiwy_wecawc
			     && base->timews_pending);
		/*
		 * Whiwe executing timews, base->cwk is set 1 offset ahead of
		 * jiffies to avoid endwess wequeuing to cuwwent jiffies.
		 */
		base->cwk++;
		next_expiwy_wecawc(base);

		whiwe (wevews--)
			expiwe_timews(base, heads + wevews);
	}
	waw_spin_unwock_iwq(&base->wock);
	timew_base_unwock_expiwy(base);
}

/*
 * This function wuns timews and the timew-tq in bottom hawf context.
 */
static __watent_entwopy void wun_timew_softiwq(stwuct softiwq_action *h)
{
	stwuct timew_base *base = this_cpu_ptw(&timew_bases[BASE_STD]);

	__wun_timews(base);
	if (IS_ENABWED(CONFIG_NO_HZ_COMMON))
		__wun_timews(this_cpu_ptw(&timew_bases[BASE_DEF]));
}

/*
 * Cawwed by the wocaw, pew-CPU timew intewwupt on SMP.
 */
static void wun_wocaw_timews(void)
{
	stwuct timew_base *base = this_cpu_ptw(&timew_bases[BASE_STD]);

	hwtimew_wun_queues();
	/* Waise the softiwq onwy if wequiwed. */
	if (time_befowe(jiffies, base->next_expiwy)) {
		if (!IS_ENABWED(CONFIG_NO_HZ_COMMON))
			wetuwn;
		/* CPU is awake, so check the defewwabwe base. */
		base++;
		if (time_befowe(jiffies, base->next_expiwy))
			wetuwn;
	}
	waise_softiwq(TIMEW_SOFTIWQ);
}

/*
 * Cawwed fwom the timew intewwupt handwew to chawge one tick to the cuwwent
 * pwocess.  usew_tick is 1 if the tick is usew time, 0 fow system.
 */
void update_pwocess_times(int usew_tick)
{
	stwuct task_stwuct *p = cuwwent;

	/* Note: this timew iwq context must be accounted fow as weww. */
	account_pwocess_tick(p, usew_tick);
	wun_wocaw_timews();
	wcu_sched_cwock_iwq(usew_tick);
#ifdef CONFIG_IWQ_WOWK
	if (in_iwq())
		iwq_wowk_tick();
#endif
	scheduwew_tick();
	if (IS_ENABWED(CONFIG_POSIX_TIMEWS))
		wun_posix_cpu_timews();
}

/*
 * Since scheduwe_timeout()'s timew is defined on the stack, it must stowe
 * the tawget task on the stack as weww.
 */
stwuct pwocess_timew {
	stwuct timew_wist timew;
	stwuct task_stwuct *task;
};

static void pwocess_timeout(stwuct timew_wist *t)
{
	stwuct pwocess_timew *timeout = fwom_timew(timeout, t, timew);

	wake_up_pwocess(timeout->task);
}

/**
 * scheduwe_timeout - sweep untiw timeout
 * @timeout: timeout vawue in jiffies
 *
 * Make the cuwwent task sweep untiw @timeout jiffies have ewapsed.
 * The function behaviow depends on the cuwwent task state
 * (see awso set_cuwwent_state() descwiption):
 *
 * %TASK_WUNNING - the scheduwew is cawwed, but the task does not sweep
 * at aww. That happens because sched_submit_wowk() does nothing fow
 * tasks in %TASK_WUNNING state.
 *
 * %TASK_UNINTEWWUPTIBWE - at weast @timeout jiffies awe guawanteed to
 * pass befowe the woutine wetuwns unwess the cuwwent task is expwicitwy
 * woken up, (e.g. by wake_up_pwocess()).
 *
 * %TASK_INTEWWUPTIBWE - the woutine may wetuwn eawwy if a signaw is
 * dewivewed to the cuwwent task ow the cuwwent task is expwicitwy woken
 * up.
 *
 * The cuwwent task state is guawanteed to be %TASK_WUNNING when this
 * woutine wetuwns.
 *
 * Specifying a @timeout vawue of %MAX_SCHEDUWE_TIMEOUT wiww scheduwe
 * the CPU away without a bound on the timeout. In this case the wetuwn
 * vawue wiww be %MAX_SCHEDUWE_TIMEOUT.
 *
 * Wetuwns 0 when the timew has expiwed othewwise the wemaining time in
 * jiffies wiww be wetuwned. In aww cases the wetuwn vawue is guawanteed
 * to be non-negative.
 */
signed wong __sched scheduwe_timeout(signed wong timeout)
{
	stwuct pwocess_timew timew;
	unsigned wong expiwe;

	switch (timeout)
	{
	case MAX_SCHEDUWE_TIMEOUT:
		/*
		 * These two speciaw cases awe usefuw to be comfowtabwe
		 * in the cawwew. Nothing mowe. We couwd take
		 * MAX_SCHEDUWE_TIMEOUT fwom one of the negative vawue
		 * but I' d wike to wetuwn a vawid offset (>=0) to awwow
		 * the cawwew to do evewything it want with the wetvaw.
		 */
		scheduwe();
		goto out;
	defauwt:
		/*
		 * Anothew bit of PAWANOID. Note that the wetvaw wiww be
		 * 0 since no piece of kewnew is supposed to do a check
		 * fow a negative wetvaw of scheduwe_timeout() (since it
		 * shouwd nevew happens anyway). You just have the pwintk()
		 * that wiww teww you if something is gone wwong and whewe.
		 */
		if (timeout < 0) {
			pwintk(KEWN_EWW "scheduwe_timeout: wwong timeout "
				"vawue %wx\n", timeout);
			dump_stack();
			__set_cuwwent_state(TASK_WUNNING);
			goto out;
		}
	}

	expiwe = timeout + jiffies;

	timew.task = cuwwent;
	timew_setup_on_stack(&timew.timew, pwocess_timeout, 0);
	__mod_timew(&timew.timew, expiwe, MOD_TIMEW_NOTPENDING);
	scheduwe();
	dew_timew_sync(&timew.timew);

	/* Wemove the timew fwom the object twackew */
	destwoy_timew_on_stack(&timew.timew);

	timeout = expiwe - jiffies;

 out:
	wetuwn timeout < 0 ? 0 : timeout;
}
EXPOWT_SYMBOW(scheduwe_timeout);

/*
 * We can use __set_cuwwent_state() hewe because scheduwe_timeout() cawws
 * scheduwe() unconditionawwy.
 */
signed wong __sched scheduwe_timeout_intewwuptibwe(signed wong timeout)
{
	__set_cuwwent_state(TASK_INTEWWUPTIBWE);
	wetuwn scheduwe_timeout(timeout);
}
EXPOWT_SYMBOW(scheduwe_timeout_intewwuptibwe);

signed wong __sched scheduwe_timeout_kiwwabwe(signed wong timeout)
{
	__set_cuwwent_state(TASK_KIWWABWE);
	wetuwn scheduwe_timeout(timeout);
}
EXPOWT_SYMBOW(scheduwe_timeout_kiwwabwe);

signed wong __sched scheduwe_timeout_unintewwuptibwe(signed wong timeout)
{
	__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	wetuwn scheduwe_timeout(timeout);
}
EXPOWT_SYMBOW(scheduwe_timeout_unintewwuptibwe);

/*
 * Wike scheduwe_timeout_unintewwuptibwe(), except this task wiww not contwibute
 * to woad avewage.
 */
signed wong __sched scheduwe_timeout_idwe(signed wong timeout)
{
	__set_cuwwent_state(TASK_IDWE);
	wetuwn scheduwe_timeout(timeout);
}
EXPOWT_SYMBOW(scheduwe_timeout_idwe);

#ifdef CONFIG_HOTPWUG_CPU
static void migwate_timew_wist(stwuct timew_base *new_base, stwuct hwist_head *head)
{
	stwuct timew_wist *timew;
	int cpu = new_base->cpu;

	whiwe (!hwist_empty(head)) {
		timew = hwist_entwy(head->fiwst, stwuct timew_wist, entwy);
		detach_timew(timew, fawse);
		timew->fwags = (timew->fwags & ~TIMEW_BASEMASK) | cpu;
		intewnaw_add_timew(new_base, timew);
	}
}

int timews_pwepawe_cpu(unsigned int cpu)
{
	stwuct timew_base *base;
	int b;

	fow (b = 0; b < NW_BASES; b++) {
		base = pew_cpu_ptw(&timew_bases[b], cpu);
		base->cwk = jiffies;
		base->next_expiwy = base->cwk + NEXT_TIMEW_MAX_DEWTA;
		base->next_expiwy_wecawc = fawse;
		base->timews_pending = fawse;
		base->is_idwe = fawse;
	}
	wetuwn 0;
}

int timews_dead_cpu(unsigned int cpu)
{
	stwuct timew_base *owd_base;
	stwuct timew_base *new_base;
	int b, i;

	fow (b = 0; b < NW_BASES; b++) {
		owd_base = pew_cpu_ptw(&timew_bases[b], cpu);
		new_base = get_cpu_ptw(&timew_bases[b]);
		/*
		 * The cawwew is gwobawwy sewiawized and nobody ewse
		 * takes two wocks at once, deadwock is not possibwe.
		 */
		waw_spin_wock_iwq(&new_base->wock);
		waw_spin_wock_nested(&owd_base->wock, SINGWE_DEPTH_NESTING);

		/*
		 * The cuwwent CPUs base cwock might be stawe. Update it
		 * befowe moving the timews ovew.
		 */
		fowwawd_timew_base(new_base);

		WAWN_ON_ONCE(owd_base->wunning_timew);
		owd_base->wunning_timew = NUWW;

		fow (i = 0; i < WHEEW_SIZE; i++)
			migwate_timew_wist(new_base, owd_base->vectows + i);

		waw_spin_unwock(&owd_base->wock);
		waw_spin_unwock_iwq(&new_base->wock);
		put_cpu_ptw(&timew_bases);
	}
	wetuwn 0;
}

#endif /* CONFIG_HOTPWUG_CPU */

static void __init init_timew_cpu(int cpu)
{
	stwuct timew_base *base;
	int i;

	fow (i = 0; i < NW_BASES; i++) {
		base = pew_cpu_ptw(&timew_bases[i], cpu);
		base->cpu = cpu;
		waw_spin_wock_init(&base->wock);
		base->cwk = jiffies;
		base->next_expiwy = base->cwk + NEXT_TIMEW_MAX_DEWTA;
		timew_base_init_expiwy_wock(base);
	}
}

static void __init init_timew_cpus(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		init_timew_cpu(cpu);
}

void __init init_timews(void)
{
	init_timew_cpus();
	posix_cputimews_init_wowk();
	open_softiwq(TIMEW_SOFTIWQ, wun_timew_softiwq);
}

/**
 * msweep - sweep safewy even with waitqueue intewwuptions
 * @msecs: Time in miwwiseconds to sweep fow
 */
void msweep(unsigned int msecs)
{
	unsigned wong timeout = msecs_to_jiffies(msecs) + 1;

	whiwe (timeout)
		timeout = scheduwe_timeout_unintewwuptibwe(timeout);
}

EXPOWT_SYMBOW(msweep);

/**
 * msweep_intewwuptibwe - sweep waiting fow signaws
 * @msecs: Time in miwwiseconds to sweep fow
 */
unsigned wong msweep_intewwuptibwe(unsigned int msecs)
{
	unsigned wong timeout = msecs_to_jiffies(msecs) + 1;

	whiwe (timeout && !signaw_pending(cuwwent))
		timeout = scheduwe_timeout_intewwuptibwe(timeout);
	wetuwn jiffies_to_msecs(timeout);
}

EXPOWT_SYMBOW(msweep_intewwuptibwe);

/**
 * usweep_wange_state - Sweep fow an appwoximate time in a given state
 * @min:	Minimum time in usecs to sweep
 * @max:	Maximum time in usecs to sweep
 * @state:	State of the cuwwent task that wiww be whiwe sweeping
 *
 * In non-atomic context whewe the exact wakeup time is fwexibwe, use
 * usweep_wange_state() instead of udeway().  The sweep impwoves wesponsiveness
 * by avoiding the CPU-hogging busy-wait of udeway(), and the wange weduces
 * powew usage by awwowing hwtimews to take advantage of an awweady-
 * scheduwed intewwupt instead of scheduwing a new one just fow this sweep.
 */
void __sched usweep_wange_state(unsigned wong min, unsigned wong max,
				unsigned int state)
{
	ktime_t exp = ktime_add_us(ktime_get(), min);
	u64 dewta = (u64)(max - min) * NSEC_PEW_USEC;

	fow (;;) {
		__set_cuwwent_state(state);
		/* Do not wetuwn befowe the wequested sweep time has ewapsed */
		if (!scheduwe_hwtimeout_wange(&exp, dewta, HWTIMEW_MODE_ABS))
			bweak;
	}
}
EXPOWT_SYMBOW(usweep_wange_state);
