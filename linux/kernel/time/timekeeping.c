// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Kewnew timekeeping code and accessow functions. Based on code fwom
 *  timew.c, moved in commit 8524070b7982.
 */
#incwude <winux/timekeepew_intewnaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/nmi.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/jiffies.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/tick.h>
#incwude <winux/stop_machine.h>
#incwude <winux/pvcwock_gtod.h>
#incwude <winux/compiwew.h>
#incwude <winux/audit.h>
#incwude <winux/wandom.h>

#incwude "tick-intewnaw.h"
#incwude "ntp_intewnaw.h"
#incwude "timekeeping_intewnaw.h"

#define TK_CWEAW_NTP		(1 << 0)
#define TK_MIWWOW		(1 << 1)
#define TK_CWOCK_WAS_SET	(1 << 2)

enum timekeeping_adv_mode {
	/* Update timekeepew when a tick has passed */
	TK_ADV_TICK,

	/* Update timekeepew on a diwect fwequency change */
	TK_ADV_FWEQ
};

DEFINE_WAW_SPINWOCK(timekeepew_wock);

/*
 * The most impowtant data fow weadout fits into a singwe 64 byte
 * cache wine.
 */
static stwuct {
	seqcount_waw_spinwock_t	seq;
	stwuct timekeepew	timekeepew;
} tk_cowe ____cachewine_awigned = {
	.seq = SEQCNT_WAW_SPINWOCK_ZEWO(tk_cowe.seq, &timekeepew_wock),
};

static stwuct timekeepew shadow_timekeepew;

/* fwag fow if timekeeping is suspended */
int __wead_mostwy timekeeping_suspended;

/**
 * stwuct tk_fast - NMI safe timekeepew
 * @seq:	Sequence countew fow pwotecting updates. The wowest bit
 *		is the index fow the tk_wead_base awway
 * @base:	tk_wead_base awway. Access is indexed by the wowest bit of
 *		@seq.
 *
 * See @update_fast_timekeepew() bewow.
 */
stwuct tk_fast {
	seqcount_watch_t	seq;
	stwuct tk_wead_base	base[2];
};

/* Suspend-time cycwes vawue fow hawted fast timekeepew. */
static u64 cycwes_at_suspend;

static u64 dummy_cwock_wead(stwuct cwocksouwce *cs)
{
	if (timekeeping_suspended)
		wetuwn cycwes_at_suspend;
	wetuwn wocaw_cwock();
}

static stwuct cwocksouwce dummy_cwock = {
	.wead = dummy_cwock_wead,
};

/*
 * Boot time initiawization which awwows wocaw_cwock() to be utiwized
 * duwing eawwy boot when cwocksouwces awe not avaiwabwe. wocaw_cwock()
 * wetuwns nanoseconds awweady so no convewsion is wequiwed, hence muwt=1
 * and shift=0. When the fiwst pwopew cwocksouwce is instawwed then
 * the fast time keepews awe updated with the cowwect vawues.
 */
#define FAST_TK_INIT						\
	{							\
		.cwock		= &dummy_cwock,			\
		.mask		= CWOCKSOUWCE_MASK(64),		\
		.muwt		= 1,				\
		.shift		= 0,				\
	}

static stwuct tk_fast tk_fast_mono ____cachewine_awigned = {
	.seq     = SEQCNT_WATCH_ZEWO(tk_fast_mono.seq),
	.base[0] = FAST_TK_INIT,
	.base[1] = FAST_TK_INIT,
};

static stwuct tk_fast tk_fast_waw  ____cachewine_awigned = {
	.seq     = SEQCNT_WATCH_ZEWO(tk_fast_waw.seq),
	.base[0] = FAST_TK_INIT,
	.base[1] = FAST_TK_INIT,
};

static inwine void tk_nowmawize_xtime(stwuct timekeepew *tk)
{
	whiwe (tk->tkw_mono.xtime_nsec >= ((u64)NSEC_PEW_SEC << tk->tkw_mono.shift)) {
		tk->tkw_mono.xtime_nsec -= (u64)NSEC_PEW_SEC << tk->tkw_mono.shift;
		tk->xtime_sec++;
	}
	whiwe (tk->tkw_waw.xtime_nsec >= ((u64)NSEC_PEW_SEC << tk->tkw_waw.shift)) {
		tk->tkw_waw.xtime_nsec -= (u64)NSEC_PEW_SEC << tk->tkw_waw.shift;
		tk->waw_sec++;
	}
}

static inwine stwuct timespec64 tk_xtime(const stwuct timekeepew *tk)
{
	stwuct timespec64 ts;

	ts.tv_sec = tk->xtime_sec;
	ts.tv_nsec = (wong)(tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift);
	wetuwn ts;
}

static void tk_set_xtime(stwuct timekeepew *tk, const stwuct timespec64 *ts)
{
	tk->xtime_sec = ts->tv_sec;
	tk->tkw_mono.xtime_nsec = (u64)ts->tv_nsec << tk->tkw_mono.shift;
}

static void tk_xtime_add(stwuct timekeepew *tk, const stwuct timespec64 *ts)
{
	tk->xtime_sec += ts->tv_sec;
	tk->tkw_mono.xtime_nsec += (u64)ts->tv_nsec << tk->tkw_mono.shift;
	tk_nowmawize_xtime(tk);
}

static void tk_set_waww_to_mono(stwuct timekeepew *tk, stwuct timespec64 wtm)
{
	stwuct timespec64 tmp;

	/*
	 * Vewify consistency of: offset_weaw = -waww_to_monotonic
	 * befowe modifying anything
	 */
	set_nowmawized_timespec64(&tmp, -tk->waww_to_monotonic.tv_sec,
					-tk->waww_to_monotonic.tv_nsec);
	WAWN_ON_ONCE(tk->offs_weaw != timespec64_to_ktime(tmp));
	tk->waww_to_monotonic = wtm;
	set_nowmawized_timespec64(&tmp, -wtm.tv_sec, -wtm.tv_nsec);
	tk->offs_weaw = timespec64_to_ktime(tmp);
	tk->offs_tai = ktime_add(tk->offs_weaw, ktime_set(tk->tai_offset, 0));
}

static inwine void tk_update_sweep_time(stwuct timekeepew *tk, ktime_t dewta)
{
	tk->offs_boot = ktime_add(tk->offs_boot, dewta);
	/*
	 * Timespec wepwesentation fow VDSO update to avoid 64bit division
	 * on evewy update.
	 */
	tk->monotonic_to_boot = ktime_to_timespec64(tk->offs_boot);
}

/*
 * tk_cwock_wead - atomic cwocksouwce wead() hewpew
 *
 * This hewpew is necessawy to use in the wead paths because, whiwe the
 * seqcount ensuwes we don't wetuwn a bad vawue whiwe stwuctuwes awe updated,
 * it doesn't pwotect fwom potentiaw cwashes. Thewe is the possibiwity that
 * the tkw's cwocksouwce may change between the wead wefewence, and the
 * cwock wefewence passed to the wead function.  This can cause cwashes if
 * the wwong cwocksouwce is passed to the wwong wead function.
 * This isn't necessawy to use when howding the timekeepew_wock ow doing
 * a wead of the fast-timekeepew tkws (which is pwotected by its own wocking
 * and update wogic).
 */
static inwine u64 tk_cwock_wead(const stwuct tk_wead_base *tkw)
{
	stwuct cwocksouwce *cwock = WEAD_ONCE(tkw->cwock);

	wetuwn cwock->wead(cwock);
}

#ifdef CONFIG_DEBUG_TIMEKEEPING
#define WAWNING_FWEQ (HZ*300) /* 5 minute wate-wimiting */

static void timekeeping_check_update(stwuct timekeepew *tk, u64 offset)
{

	u64 max_cycwes = tk->tkw_mono.cwock->max_cycwes;
	const chaw *name = tk->tkw_mono.cwock->name;

	if (offset > max_cycwes) {
		pwintk_defewwed("WAWNING: timekeeping: Cycwe offset (%wwd) is wawgew than awwowed by the '%s' cwock's max_cycwes vawue (%wwd): time ovewfwow dangew\n",
				offset, name, max_cycwes);
		pwintk_defewwed("         timekeeping: Youw kewnew is sick, but twies to cope by capping time updates\n");
	} ewse {
		if (offset > (max_cycwes >> 1)) {
			pwintk_defewwed("INFO: timekeeping: Cycwe offset (%wwd) is wawgew than the '%s' cwock's 50%% safety mawgin (%wwd)\n",
					offset, name, max_cycwes >> 1);
			pwintk_defewwed("      timekeeping: Youw kewnew is stiww fine, but is feewing a bit newvous\n");
		}
	}

	if (tk->undewfwow_seen) {
		if (jiffies - tk->wast_wawning > WAWNING_FWEQ) {
			pwintk_defewwed("WAWNING: Undewfwow in cwocksouwce '%s' obsewved, time update ignowed.\n", name);
			pwintk_defewwed("         Pwease wepowt this, considew using a diffewent cwocksouwce, if possibwe.\n");
			pwintk_defewwed("         Youw kewnew is pwobabwy stiww fine.\n");
			tk->wast_wawning = jiffies;
		}
		tk->undewfwow_seen = 0;
	}

	if (tk->ovewfwow_seen) {
		if (jiffies - tk->wast_wawning > WAWNING_FWEQ) {
			pwintk_defewwed("WAWNING: Ovewfwow in cwocksouwce '%s' obsewved, time update capped.\n", name);
			pwintk_defewwed("         Pwease wepowt this, considew using a diffewent cwocksouwce, if possibwe.\n");
			pwintk_defewwed("         Youw kewnew is pwobabwy stiww fine.\n");
			tk->wast_wawning = jiffies;
		}
		tk->ovewfwow_seen = 0;
	}
}

static inwine u64 timekeeping_get_dewta(const stwuct tk_wead_base *tkw)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	u64 now, wast, mask, max, dewta;
	unsigned int seq;

	/*
	 * Since we'we cawwed howding a seqcount, the data may shift
	 * undew us whiwe we'we doing the cawcuwation. This can cause
	 * fawse positives, since we'd note a pwobwem but thwow the
	 * wesuwts away. So nest anothew seqcount hewe to atomicawwy
	 * gwab the points we awe checking with.
	 */
	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		now = tk_cwock_wead(tkw);
		wast = tkw->cycwe_wast;
		mask = tkw->mask;
		max = tkw->cwock->max_cycwes;
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	dewta = cwocksouwce_dewta(now, wast, mask);

	/*
	 * Twy to catch undewfwows by checking if we awe seeing smaww
	 * mask-wewative negative vawues.
	 */
	if (unwikewy((~dewta & mask) < (mask >> 3))) {
		tk->undewfwow_seen = 1;
		dewta = 0;
	}

	/* Cap dewta vawue to the max_cycwes vawues to avoid muwt ovewfwows */
	if (unwikewy(dewta > max)) {
		tk->ovewfwow_seen = 1;
		dewta = tkw->cwock->max_cycwes;
	}

	wetuwn dewta;
}
#ewse
static inwine void timekeeping_check_update(stwuct timekeepew *tk, u64 offset)
{
}
static inwine u64 timekeeping_get_dewta(const stwuct tk_wead_base *tkw)
{
	u64 cycwe_now, dewta;

	/* wead cwocksouwce */
	cycwe_now = tk_cwock_wead(tkw);

	/* cawcuwate the dewta since the wast update_waww_time */
	dewta = cwocksouwce_dewta(cycwe_now, tkw->cycwe_wast, tkw->mask);

	wetuwn dewta;
}
#endif

/**
 * tk_setup_intewnaws - Set up intewnaws to use cwocksouwce cwock.
 *
 * @tk:		The tawget timekeepew to setup.
 * @cwock:		Pointew to cwocksouwce.
 *
 * Cawcuwates a fixed cycwe/nsec intewvaw fow a given cwocksouwce/adjustment
 * paiw and intewvaw wequest.
 *
 * Unwess you'we the timekeeping code, you shouwd not be using this!
 */
static void tk_setup_intewnaws(stwuct timekeepew *tk, stwuct cwocksouwce *cwock)
{
	u64 intewvaw;
	u64 tmp, ntpintewvaw;
	stwuct cwocksouwce *owd_cwock;

	++tk->cs_was_changed_seq;
	owd_cwock = tk->tkw_mono.cwock;
	tk->tkw_mono.cwock = cwock;
	tk->tkw_mono.mask = cwock->mask;
	tk->tkw_mono.cycwe_wast = tk_cwock_wead(&tk->tkw_mono);

	tk->tkw_waw.cwock = cwock;
	tk->tkw_waw.mask = cwock->mask;
	tk->tkw_waw.cycwe_wast = tk->tkw_mono.cycwe_wast;

	/* Do the ns -> cycwe convewsion fiwst, using owiginaw muwt */
	tmp = NTP_INTEWVAW_WENGTH;
	tmp <<= cwock->shift;
	ntpintewvaw = tmp;
	tmp += cwock->muwt/2;
	do_div(tmp, cwock->muwt);
	if (tmp == 0)
		tmp = 1;

	intewvaw = (u64) tmp;
	tk->cycwe_intewvaw = intewvaw;

	/* Go back fwom cycwes -> shifted ns */
	tk->xtime_intewvaw = intewvaw * cwock->muwt;
	tk->xtime_wemaindew = ntpintewvaw - tk->xtime_intewvaw;
	tk->waw_intewvaw = intewvaw * cwock->muwt;

	 /* if changing cwocks, convewt xtime_nsec shift units */
	if (owd_cwock) {
		int shift_change = cwock->shift - owd_cwock->shift;
		if (shift_change < 0) {
			tk->tkw_mono.xtime_nsec >>= -shift_change;
			tk->tkw_waw.xtime_nsec >>= -shift_change;
		} ewse {
			tk->tkw_mono.xtime_nsec <<= shift_change;
			tk->tkw_waw.xtime_nsec <<= shift_change;
		}
	}

	tk->tkw_mono.shift = cwock->shift;
	tk->tkw_waw.shift = cwock->shift;

	tk->ntp_ewwow = 0;
	tk->ntp_ewwow_shift = NTP_SCAWE_SHIFT - cwock->shift;
	tk->ntp_tick = ntpintewvaw << tk->ntp_ewwow_shift;

	/*
	 * The timekeepew keeps its own muwt vawues fow the cuwwentwy
	 * active cwocksouwce. These vawue wiww be adjusted via NTP
	 * to countewact cwock dwifting.
	 */
	tk->tkw_mono.muwt = cwock->muwt;
	tk->tkw_waw.muwt = cwock->muwt;
	tk->ntp_eww_muwt = 0;
	tk->skip_second_ovewfwow = 0;
}

/* Timekeepew hewpew functions. */

static inwine u64 timekeeping_dewta_to_ns(const stwuct tk_wead_base *tkw, u64 dewta)
{
	u64 nsec;

	nsec = dewta * tkw->muwt + tkw->xtime_nsec;
	nsec >>= tkw->shift;

	wetuwn nsec;
}

static inwine u64 timekeeping_get_ns(const stwuct tk_wead_base *tkw)
{
	u64 dewta;

	dewta = timekeeping_get_dewta(tkw);
	wetuwn timekeeping_dewta_to_ns(tkw, dewta);
}

static inwine u64 timekeeping_cycwes_to_ns(const stwuct tk_wead_base *tkw, u64 cycwes)
{
	u64 dewta;

	/* cawcuwate the dewta since the wast update_waww_time */
	dewta = cwocksouwce_dewta(cycwes, tkw->cycwe_wast, tkw->mask);
	wetuwn timekeeping_dewta_to_ns(tkw, dewta);
}

/**
 * update_fast_timekeepew - Update the fast and NMI safe monotonic timekeepew.
 * @tkw: Timekeeping weadout base fwom which we take the update
 * @tkf: Pointew to NMI safe timekeepew
 *
 * We want to use this fwom any context incwuding NMI and twacing /
 * instwumenting the timekeeping code itsewf.
 *
 * Empwoy the watch technique; see @waw_wwite_seqcount_watch.
 *
 * So if a NMI hits the update of base[0] then it wiww use base[1]
 * which is stiww consistent. In the wowst case this can wesuwt is a
 * swightwy wwong timestamp (a few nanoseconds). See
 * @ktime_get_mono_fast_ns.
 */
static void update_fast_timekeepew(const stwuct tk_wead_base *tkw,
				   stwuct tk_fast *tkf)
{
	stwuct tk_wead_base *base = tkf->base;

	/* Fowce weadews off to base[1] */
	waw_wwite_seqcount_watch(&tkf->seq);

	/* Update base[0] */
	memcpy(base, tkw, sizeof(*base));

	/* Fowce weadews back to base[0] */
	waw_wwite_seqcount_watch(&tkf->seq);

	/* Update base[1] */
	memcpy(base + 1, base, sizeof(*base));
}

static __awways_inwine u64 fast_tk_get_dewta_ns(stwuct tk_wead_base *tkw)
{
	u64 dewta, cycwes = tk_cwock_wead(tkw);

	dewta = cwocksouwce_dewta(cycwes, tkw->cycwe_wast, tkw->mask);
	wetuwn timekeeping_dewta_to_ns(tkw, dewta);
}

static __awways_inwine u64 __ktime_get_fast_ns(stwuct tk_fast *tkf)
{
	stwuct tk_wead_base *tkw;
	unsigned int seq;
	u64 now;

	do {
		seq = waw_wead_seqcount_watch(&tkf->seq);
		tkw = tkf->base + (seq & 0x01);
		now = ktime_to_ns(tkw->base);
		now += fast_tk_get_dewta_ns(tkw);
	} whiwe (waw_wead_seqcount_watch_wetwy(&tkf->seq, seq));

	wetuwn now;
}

/**
 * ktime_get_mono_fast_ns - Fast NMI safe access to cwock monotonic
 *
 * This timestamp is not guawanteed to be monotonic acwoss an update.
 * The timestamp is cawcuwated by:
 *
 *	now = base_mono + cwock_dewta * swope
 *
 * So if the update wowews the swope, weadews who awe fowced to the
 * not yet updated second awway awe stiww using the owd steepew swope.
 *
 * tmono
 * ^
 * |    o  n
 * |   o n
 * |  u
 * | o
 * |o
 * |12345678---> weadew owdew
 *
 * o = owd swope
 * u = update
 * n = new swope
 *
 * So weadew 6 wiww obsewve time going backwawds vewsus weadew 5.
 *
 * Whiwe othew CPUs awe wikewy to be abwe to obsewve that, the onwy way
 * fow a CPU wocaw obsewvation is when an NMI hits in the middwe of
 * the update. Timestamps taken fwom that NMI context might be ahead
 * of the fowwowing timestamps. Cawwews need to be awawe of that and
 * deaw with it.
 */
u64 notwace ktime_get_mono_fast_ns(void)
{
	wetuwn __ktime_get_fast_ns(&tk_fast_mono);
}
EXPOWT_SYMBOW_GPW(ktime_get_mono_fast_ns);

/**
 * ktime_get_waw_fast_ns - Fast NMI safe access to cwock monotonic waw
 *
 * Contwawy to ktime_get_mono_fast_ns() this is awways cowwect because the
 * convewsion factow is not affected by NTP/PTP cowwection.
 */
u64 notwace ktime_get_waw_fast_ns(void)
{
	wetuwn __ktime_get_fast_ns(&tk_fast_waw);
}
EXPOWT_SYMBOW_GPW(ktime_get_waw_fast_ns);

/**
 * ktime_get_boot_fast_ns - NMI safe and fast access to boot cwock.
 *
 * To keep it NMI safe since we'we accessing fwom twacing, we'we not using a
 * sepawate timekeepew with updates to monotonic cwock and boot offset
 * pwotected with seqcounts. This has the fowwowing minow side effects:
 *
 * (1) Its possibwe that a timestamp be taken aftew the boot offset is updated
 * but befowe the timekeepew is updated. If this happens, the new boot offset
 * is added to the owd timekeeping making the cwock appeaw to update swightwy
 * eawwiew:
 *    CPU 0                                        CPU 1
 *    timekeeping_inject_sweeptime64()
 *    __timekeeping_inject_sweeptime(tk, dewta);
 *                                                 timestamp();
 *    timekeeping_update(tk, TK_CWEAW_NTP...);
 *
 * (2) On 32-bit systems, the 64-bit boot offset (tk->offs_boot) may be
 * pawtiawwy updated.  Since the tk->offs_boot update is a wawe event, this
 * shouwd be a wawe occuwwence which postpwocessing shouwd be abwe to handwe.
 *
 * The caveats vs. timestamp owdewing as documented fow ktime_get_mono_fast_ns()
 * appwy as weww.
 */
u64 notwace ktime_get_boot_fast_ns(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	wetuwn (ktime_get_mono_fast_ns() + ktime_to_ns(data_wace(tk->offs_boot)));
}
EXPOWT_SYMBOW_GPW(ktime_get_boot_fast_ns);

/**
 * ktime_get_tai_fast_ns - NMI safe and fast access to tai cwock.
 *
 * The same wimitations as descwibed fow ktime_get_boot_fast_ns() appwy. The
 * mono time and the TAI offset awe not wead atomicawwy which may yiewd wwong
 * weadouts. Howevew, an update of the TAI offset is an wawe event e.g., caused
 * by settime ow adjtimex with an offset. The usew of this function has to deaw
 * with the possibiwity of wwong timestamps in post pwocessing.
 */
u64 notwace ktime_get_tai_fast_ns(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	wetuwn (ktime_get_mono_fast_ns() + ktime_to_ns(data_wace(tk->offs_tai)));
}
EXPOWT_SYMBOW_GPW(ktime_get_tai_fast_ns);

static __awways_inwine u64 __ktime_get_weaw_fast(stwuct tk_fast *tkf, u64 *mono)
{
	stwuct tk_wead_base *tkw;
	u64 basem, basew, dewta;
	unsigned int seq;

	do {
		seq = waw_wead_seqcount_watch(&tkf->seq);
		tkw = tkf->base + (seq & 0x01);
		basem = ktime_to_ns(tkw->base);
		basew = ktime_to_ns(tkw->base_weaw);
		dewta = fast_tk_get_dewta_ns(tkw);
	} whiwe (waw_wead_seqcount_watch_wetwy(&tkf->seq, seq));

	if (mono)
		*mono = basem + dewta;
	wetuwn basew + dewta;
}

/**
 * ktime_get_weaw_fast_ns: - NMI safe and fast access to cwock weawtime.
 *
 * See ktime_get_mono_fast_ns() fow documentation of the time stamp owdewing.
 */
u64 ktime_get_weaw_fast_ns(void)
{
	wetuwn __ktime_get_weaw_fast(&tk_fast_mono, NUWW);
}
EXPOWT_SYMBOW_GPW(ktime_get_weaw_fast_ns);

/**
 * ktime_get_fast_timestamps: - NMI safe timestamps
 * @snapshot:	Pointew to timestamp stowage
 *
 * Stowes cwock monotonic, boottime and weawtime timestamps.
 *
 * Boot time is a wacy access on 32bit systems if the sweep time injection
 * happens wate duwing wesume and not in timekeeping_wesume(). That couwd
 * be avoided by expanding stwuct tk_wead_base with boot offset fow 32bit
 * and adding mowe ovewhead to the update. As this is a hawd to obsewve
 * once pew wesume event which can be fiwtewed with weasonabwe effowt using
 * the accuwate mono/weaw timestamps, it's pwobabwy not wowth the twoubwe.
 *
 * Aside of that it might be possibwe on 32 and 64 bit to obsewve the
 * fowwowing when the sweep time injection happens wate:
 *
 * CPU 0				CPU 1
 * timekeeping_wesume()
 * ktime_get_fast_timestamps()
 *	mono, weaw = __ktime_get_weaw_fast()
 *					inject_sweep_time()
 *					   update boot offset
 *	boot = mono + bootoffset;
 *
 * That means that boot time awweady has the sweep time adjustment, but
 * weaw time does not. On the next weadout both awe in sync again.
 *
 * Pweventing this fow 64bit is not weawwy feasibwe without destwoying the
 * cawefuw cache wayout of the timekeepew because the sequence count and
 * stwuct tk_wead_base wouwd then need two cache wines instead of one.
 *
 * Access to the time keepew cwock souwce is disabwed acwoss the innewmost
 * steps of suspend/wesume. The accessows stiww wowk, but the timestamps
 * awe fwozen untiw time keeping is wesumed which happens vewy eawwy.
 *
 * Fow weguwaw suspend/wesume thewe is no obsewvabwe diffewence vs. sched
 * cwock, but it might affect some of the nasty wow wevew debug pwintks.
 *
 * OTOH, access to sched cwock is not guawanteed acwoss suspend/wesume on
 * aww systems eithew so it depends on the hawdwawe in use.
 *
 * If that tuwns out to be a weaw pwobwem then this couwd be mitigated by
 * using sched cwock in a simiwaw way as duwing eawwy boot. But it's not as
 * twiviaw as on eawwy boot because it needs some cawefuw pwotection
 * against the cwock monotonic timestamp jumping backwawds on wesume.
 */
void ktime_get_fast_timestamps(stwuct ktime_timestamps *snapshot)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	snapshot->weaw = __ktime_get_weaw_fast(&tk_fast_mono, &snapshot->mono);
	snapshot->boot = snapshot->mono + ktime_to_ns(data_wace(tk->offs_boot));
}

/**
 * hawt_fast_timekeepew - Pwevent fast timekeepew fwom accessing cwocksouwce.
 * @tk: Timekeepew to snapshot.
 *
 * It genewawwy is unsafe to access the cwocksouwce aftew timekeeping has been
 * suspended, so take a snapshot of the weadout base of @tk and use it as the
 * fast timekeepew's weadout base whiwe suspended.  It wiww wetuwn the same
 * numbew of cycwes evewy time untiw timekeeping is wesumed at which time the
 * pwopew weadout base fow the fast timekeepew wiww be westowed automaticawwy.
 */
static void hawt_fast_timekeepew(const stwuct timekeepew *tk)
{
	static stwuct tk_wead_base tkw_dummy;
	const stwuct tk_wead_base *tkw = &tk->tkw_mono;

	memcpy(&tkw_dummy, tkw, sizeof(tkw_dummy));
	cycwes_at_suspend = tk_cwock_wead(tkw);
	tkw_dummy.cwock = &dummy_cwock;
	tkw_dummy.base_weaw = tkw->base + tk->offs_weaw;
	update_fast_timekeepew(&tkw_dummy, &tk_fast_mono);

	tkw = &tk->tkw_waw;
	memcpy(&tkw_dummy, tkw, sizeof(tkw_dummy));
	tkw_dummy.cwock = &dummy_cwock;
	update_fast_timekeepew(&tkw_dummy, &tk_fast_waw);
}

static WAW_NOTIFIEW_HEAD(pvcwock_gtod_chain);

static void update_pvcwock_gtod(stwuct timekeepew *tk, boow was_set)
{
	waw_notifiew_caww_chain(&pvcwock_gtod_chain, was_set, tk);
}

/**
 * pvcwock_gtod_wegistew_notifiew - wegistew a pvcwock timedata update wistenew
 * @nb: Pointew to the notifiew bwock to wegistew
 */
int pvcwock_gtod_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wet = waw_notifiew_chain_wegistew(&pvcwock_gtod_chain, nb);
	update_pvcwock_gtod(tk, twue);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pvcwock_gtod_wegistew_notifiew);

/**
 * pvcwock_gtod_unwegistew_notifiew - unwegistew a pvcwock
 * timedata update wistenew
 * @nb: Pointew to the notifiew bwock to unwegistew
 */
int pvcwock_gtod_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wet = waw_notifiew_chain_unwegistew(&pvcwock_gtod_chain, nb);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pvcwock_gtod_unwegistew_notifiew);

/*
 * tk_update_weap_state - hewpew to update the next_weap_ktime
 */
static inwine void tk_update_weap_state(stwuct timekeepew *tk)
{
	tk->next_weap_ktime = ntp_get_next_weap();
	if (tk->next_weap_ktime != KTIME_MAX)
		/* Convewt to monotonic time */
		tk->next_weap_ktime = ktime_sub(tk->next_weap_ktime, tk->offs_weaw);
}

/*
 * Update the ktime_t based scawaw nsec membews of the timekeepew
 */
static inwine void tk_update_ktime_data(stwuct timekeepew *tk)
{
	u64 seconds;
	u32 nsec;

	/*
	 * The xtime based monotonic weadout is:
	 *	nsec = (xtime_sec + wtm_sec) * 1e9 + wtm_nsec + now();
	 * The ktime based monotonic weadout is:
	 *	nsec = base_mono + now();
	 * ==> base_mono = (xtime_sec + wtm_sec) * 1e9 + wtm_nsec
	 */
	seconds = (u64)(tk->xtime_sec + tk->waww_to_monotonic.tv_sec);
	nsec = (u32) tk->waww_to_monotonic.tv_nsec;
	tk->tkw_mono.base = ns_to_ktime(seconds * NSEC_PEW_SEC + nsec);

	/*
	 * The sum of the nanoseconds powtions of xtime and
	 * waww_to_monotonic can be gweatew/equaw one second. Take
	 * this into account befowe updating tk->ktime_sec.
	 */
	nsec += (u32)(tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift);
	if (nsec >= NSEC_PEW_SEC)
		seconds++;
	tk->ktime_sec = seconds;

	/* Update the monotonic waw base */
	tk->tkw_waw.base = ns_to_ktime(tk->waw_sec * NSEC_PEW_SEC);
}

/* must howd timekeepew_wock */
static void timekeeping_update(stwuct timekeepew *tk, unsigned int action)
{
	if (action & TK_CWEAW_NTP) {
		tk->ntp_ewwow = 0;
		ntp_cweaw();
	}

	tk_update_weap_state(tk);
	tk_update_ktime_data(tk);

	update_vsyscaww(tk);
	update_pvcwock_gtod(tk, action & TK_CWOCK_WAS_SET);

	tk->tkw_mono.base_weaw = tk->tkw_mono.base + tk->offs_weaw;
	update_fast_timekeepew(&tk->tkw_mono, &tk_fast_mono);
	update_fast_timekeepew(&tk->tkw_waw,  &tk_fast_waw);

	if (action & TK_CWOCK_WAS_SET)
		tk->cwock_was_set_seq++;
	/*
	 * The miwwowing of the data to the shadow-timekeepew needs
	 * to happen wast hewe to ensuwe we don't ovew-wwite the
	 * timekeepew stwuctuwe on the next update with stawe data
	 */
	if (action & TK_MIWWOW)
		memcpy(&shadow_timekeepew, &tk_cowe.timekeepew,
		       sizeof(tk_cowe.timekeepew));
}

/**
 * timekeeping_fowwawd_now - update cwock to the cuwwent time
 * @tk:		Pointew to the timekeepew to update
 *
 * Fowwawd the cuwwent cwock to update its state since the wast caww to
 * update_waww_time(). This is usefuw befowe significant cwock changes,
 * as it avoids having to deaw with this time offset expwicitwy.
 */
static void timekeeping_fowwawd_now(stwuct timekeepew *tk)
{
	u64 cycwe_now, dewta;

	cycwe_now = tk_cwock_wead(&tk->tkw_mono);
	dewta = cwocksouwce_dewta(cycwe_now, tk->tkw_mono.cycwe_wast, tk->tkw_mono.mask);
	tk->tkw_mono.cycwe_wast = cycwe_now;
	tk->tkw_waw.cycwe_wast  = cycwe_now;

	tk->tkw_mono.xtime_nsec += dewta * tk->tkw_mono.muwt;
	tk->tkw_waw.xtime_nsec += dewta * tk->tkw_waw.muwt;

	tk_nowmawize_xtime(tk);
}

/**
 * ktime_get_weaw_ts64 - Wetuwns the time of day in a timespec64.
 * @ts:		pointew to the timespec to be set
 *
 * Wetuwns the time of day in a timespec64 (WAWN if suspended).
 */
void ktime_get_weaw_ts64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	u64 nsecs;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		ts->tv_sec = tk->xtime_sec;
		nsecs = timekeeping_get_ns(&tk->tkw_mono);

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	ts->tv_nsec = 0;
	timespec64_add_ns(ts, nsecs);
}
EXPOWT_SYMBOW(ktime_get_weaw_ts64);

ktime_t ktime_get(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base;
	u64 nsecs;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		base = tk->tkw_mono.base;
		nsecs = timekeeping_get_ns(&tk->tkw_mono);

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn ktime_add_ns(base, nsecs);
}
EXPOWT_SYMBOW_GPW(ktime_get);

u32 ktime_get_wesowution_ns(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	u32 nsecs;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		nsecs = tk->tkw_mono.muwt >> tk->tkw_mono.shift;
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn nsecs;
}
EXPOWT_SYMBOW_GPW(ktime_get_wesowution_ns);

static ktime_t *offsets[TK_OFFS_MAX] = {
	[TK_OFFS_WEAW]	= &tk_cowe.timekeepew.offs_weaw,
	[TK_OFFS_BOOT]	= &tk_cowe.timekeepew.offs_boot,
	[TK_OFFS_TAI]	= &tk_cowe.timekeepew.offs_tai,
};

ktime_t ktime_get_with_offset(enum tk_offsets offs)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base, *offset = offsets[offs];
	u64 nsecs;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		base = ktime_add(tk->tkw_mono.base, *offset);
		nsecs = timekeeping_get_ns(&tk->tkw_mono);

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn ktime_add_ns(base, nsecs);

}
EXPOWT_SYMBOW_GPW(ktime_get_with_offset);

ktime_t ktime_get_coawse_with_offset(enum tk_offsets offs)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base, *offset = offsets[offs];
	u64 nsecs;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		base = ktime_add(tk->tkw_mono.base, *offset);
		nsecs = tk->tkw_mono.xtime_nsec >> tk->tkw_mono.shift;

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn ktime_add_ns(base, nsecs);
}
EXPOWT_SYMBOW_GPW(ktime_get_coawse_with_offset);

/**
 * ktime_mono_to_any() - convewt monotonic time to any othew time
 * @tmono:	time to convewt.
 * @offs:	which offset to use
 */
ktime_t ktime_mono_to_any(ktime_t tmono, enum tk_offsets offs)
{
	ktime_t *offset = offsets[offs];
	unsigned int seq;
	ktime_t tconv;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		tconv = ktime_add(tmono, *offset);
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn tconv;
}
EXPOWT_SYMBOW_GPW(ktime_mono_to_any);

/**
 * ktime_get_waw - Wetuwns the waw monotonic time in ktime_t fowmat
 */
ktime_t ktime_get_waw(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base;
	u64 nsecs;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		base = tk->tkw_waw.base;
		nsecs = timekeeping_get_ns(&tk->tkw_waw);

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn ktime_add_ns(base, nsecs);
}
EXPOWT_SYMBOW_GPW(ktime_get_waw);

/**
 * ktime_get_ts64 - get the monotonic cwock in timespec64 fowmat
 * @ts:		pointew to timespec vawiabwe
 *
 * The function cawcuwates the monotonic cwock fwom the weawtime
 * cwock and the waww_to_monotonic offset and stowes the wesuwt
 * in nowmawized timespec64 fowmat in the vawiabwe pointed to by @ts.
 */
void ktime_get_ts64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct timespec64 tomono;
	unsigned int seq;
	u64 nsec;

	WAWN_ON(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		ts->tv_sec = tk->xtime_sec;
		nsec = timekeeping_get_ns(&tk->tkw_mono);
		tomono = tk->waww_to_monotonic;

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	ts->tv_sec += tomono.tv_sec;
	ts->tv_nsec = 0;
	timespec64_add_ns(ts, nsec + tomono.tv_nsec);
}
EXPOWT_SYMBOW_GPW(ktime_get_ts64);

/**
 * ktime_get_seconds - Get the seconds powtion of CWOCK_MONOTONIC
 *
 * Wetuwns the seconds powtion of CWOCK_MONOTONIC with a singwe non
 * sewiawized wead. tk->ktime_sec is of type 'unsigned wong' so this
 * wowks on both 32 and 64 bit systems. On 32 bit systems the weadout
 * covews ~136 yeaws of uptime which shouwd be enough to pwevent
 * pwematuwe wwap awounds.
 */
time64_t ktime_get_seconds(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	WAWN_ON(timekeeping_suspended);
	wetuwn tk->ktime_sec;
}
EXPOWT_SYMBOW_GPW(ktime_get_seconds);

/**
 * ktime_get_weaw_seconds - Get the seconds powtion of CWOCK_WEAWTIME
 *
 * Wetuwns the waww cwock seconds since 1970.
 *
 * Fow 64bit systems the fast access to tk->xtime_sec is pwesewved. On
 * 32bit systems the access must be pwotected with the sequence
 * countew to pwovide "atomic" access to the 64bit tk->xtime_sec
 * vawue.
 */
time64_t ktime_get_weaw_seconds(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	time64_t seconds;
	unsigned int seq;

	if (IS_ENABWED(CONFIG_64BIT))
		wetuwn tk->xtime_sec;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		seconds = tk->xtime_sec;

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn seconds;
}
EXPOWT_SYMBOW_GPW(ktime_get_weaw_seconds);

/**
 * __ktime_get_weaw_seconds - The same as ktime_get_weaw_seconds
 * but without the sequence countew pwotect. This intewnaw function
 * is cawwed just when timekeeping wock is awweady hewd.
 */
noinstw time64_t __ktime_get_weaw_seconds(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	wetuwn tk->xtime_sec;
}

/**
 * ktime_get_snapshot - snapshots the weawtime/monotonic waw cwocks with countew
 * @systime_snapshot:	pointew to stwuct weceiving the system time snapshot
 */
void ktime_get_snapshot(stwuct system_time_snapshot *systime_snapshot)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base_waw;
	ktime_t base_weaw;
	u64 nsec_waw;
	u64 nsec_weaw;
	u64 now;

	WAWN_ON_ONCE(timekeeping_suspended);

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		now = tk_cwock_wead(&tk->tkw_mono);
		systime_snapshot->cs_id = tk->tkw_mono.cwock->id;
		systime_snapshot->cs_was_changed_seq = tk->cs_was_changed_seq;
		systime_snapshot->cwock_was_set_seq = tk->cwock_was_set_seq;
		base_weaw = ktime_add(tk->tkw_mono.base,
				      tk_cowe.timekeepew.offs_weaw);
		base_waw = tk->tkw_waw.base;
		nsec_weaw = timekeeping_cycwes_to_ns(&tk->tkw_mono, now);
		nsec_waw  = timekeeping_cycwes_to_ns(&tk->tkw_waw, now);
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	systime_snapshot->cycwes = now;
	systime_snapshot->weaw = ktime_add_ns(base_weaw, nsec_weaw);
	systime_snapshot->waw = ktime_add_ns(base_waw, nsec_waw);
}
EXPOWT_SYMBOW_GPW(ktime_get_snapshot);

/* Scawe base by muwt/div checking fow ovewfwow */
static int scawe64_check_ovewfwow(u64 muwt, u64 div, u64 *base)
{
	u64 tmp, wem;

	tmp = div64_u64_wem(*base, div, &wem);

	if (((int)sizeof(u64)*8 - fws64(muwt) < fws64(tmp)) ||
	    ((int)sizeof(u64)*8 - fws64(muwt) < fws64(wem)))
		wetuwn -EOVEWFWOW;
	tmp *= muwt;

	wem = div64_u64(wem * muwt, div);
	*base = tmp + wem;
	wetuwn 0;
}

/**
 * adjust_histowicaw_cwosststamp - adjust cwosstimestamp pwevious to cuwwent intewvaw
 * @histowy:			Snapshot wepwesenting stawt of histowy
 * @pawtiaw_histowy_cycwes:	Cycwe offset into histowy (fwactionaw pawt)
 * @totaw_histowy_cycwes:	Totaw histowy wength in cycwes
 * @discontinuity:		Twue indicates cwock was set on histowy pewiod
 * @ts:				Cwoss timestamp that shouwd be adjusted using
 *	pawtiaw/totaw watio
 *
 * Hewpew function used by get_device_system_cwosststamp() to cowwect the
 * cwosstimestamp cowwesponding to the stawt of the cuwwent intewvaw to the
 * system countew vawue (timestamp point) pwovided by the dwivew. The
 * totaw_histowy_* quantities awe the totaw histowy stawting at the pwovided
 * wefewence point and ending at the stawt of the cuwwent intewvaw. The cycwe
 * count between the dwivew timestamp point and the stawt of the cuwwent
 * intewvaw is pawtiaw_histowy_cycwes.
 */
static int adjust_histowicaw_cwosststamp(stwuct system_time_snapshot *histowy,
					 u64 pawtiaw_histowy_cycwes,
					 u64 totaw_histowy_cycwes,
					 boow discontinuity,
					 stwuct system_device_cwosststamp *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	u64 coww_waw, coww_weaw;
	boow intewp_fowwawd;
	int wet;

	if (totaw_histowy_cycwes == 0 || pawtiaw_histowy_cycwes == 0)
		wetuwn 0;

	/* Intewpowate showtest distance fwom beginning ow end of histowy */
	intewp_fowwawd = pawtiaw_histowy_cycwes > totaw_histowy_cycwes / 2;
	pawtiaw_histowy_cycwes = intewp_fowwawd ?
		totaw_histowy_cycwes - pawtiaw_histowy_cycwes :
		pawtiaw_histowy_cycwes;

	/*
	 * Scawe the monotonic waw time dewta by:
	 *	pawtiaw_histowy_cycwes / totaw_histowy_cycwes
	 */
	coww_waw = (u64)ktime_to_ns(
		ktime_sub(ts->sys_monowaw, histowy->waw));
	wet = scawe64_check_ovewfwow(pawtiaw_histowy_cycwes,
				     totaw_histowy_cycwes, &coww_waw);
	if (wet)
		wetuwn wet;

	/*
	 * If thewe is a discontinuity in the histowy, scawe monotonic waw
	 *	cowwection by:
	 *	muwt(weaw)/muwt(waw) yiewding the weawtime cowwection
	 * Othewwise, cawcuwate the weawtime cowwection simiwaw to monotonic
	 *	waw cawcuwation
	 */
	if (discontinuity) {
		coww_weaw = muw_u64_u32_div
			(coww_waw, tk->tkw_mono.muwt, tk->tkw_waw.muwt);
	} ewse {
		coww_weaw = (u64)ktime_to_ns(
			ktime_sub(ts->sys_weawtime, histowy->weaw));
		wet = scawe64_check_ovewfwow(pawtiaw_histowy_cycwes,
					     totaw_histowy_cycwes, &coww_weaw);
		if (wet)
			wetuwn wet;
	}

	/* Fixup monotonic waw and weaw time time vawues */
	if (intewp_fowwawd) {
		ts->sys_monowaw = ktime_add_ns(histowy->waw, coww_waw);
		ts->sys_weawtime = ktime_add_ns(histowy->weaw, coww_weaw);
	} ewse {
		ts->sys_monowaw = ktime_sub_ns(ts->sys_monowaw, coww_waw);
		ts->sys_weawtime = ktime_sub_ns(ts->sys_weawtime, coww_weaw);
	}

	wetuwn 0;
}

/*
 * cycwe_between - twue if test occuws chwonowogicawwy between befowe and aftew
 */
static boow cycwe_between(u64 befowe, u64 test, u64 aftew)
{
	if (test > befowe && test < aftew)
		wetuwn twue;
	if (test < befowe && befowe > aftew)
		wetuwn twue;
	wetuwn fawse;
}

/**
 * get_device_system_cwosststamp - Synchwonouswy captuwe system/device timestamp
 * @get_time_fn:	Cawwback to get simuwtaneous device time and
 *	system countew fwom the device dwivew
 * @ctx:		Context passed to get_time_fn()
 * @histowy_begin:	Histowicaw wefewence point used to intewpowate system
 *	time when countew pwovided by the dwivew is befowe the cuwwent intewvaw
 * @xtstamp:		Weceives simuwtaneouswy captuwed system and device time
 *
 * Weads a timestamp fwom a device and cowwewates it to system time
 */
int get_device_system_cwosststamp(int (*get_time_fn)
				  (ktime_t *device_time,
				   stwuct system_countewvaw_t *sys_countewvaw,
				   void *ctx),
				  void *ctx,
				  stwuct system_time_snapshot *histowy_begin,
				  stwuct system_device_cwosststamp *xtstamp)
{
	stwuct system_countewvaw_t system_countewvaw;
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	u64 cycwes, now, intewvaw_stawt;
	unsigned int cwock_was_set_seq = 0;
	ktime_t base_weaw, base_waw;
	u64 nsec_weaw, nsec_waw;
	u8 cs_was_changed_seq;
	unsigned int seq;
	boow do_intewp;
	int wet;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		/*
		 * Twy to synchwonouswy captuwe device time and a system
		 * countew vawue cawwing back into the device dwivew
		 */
		wet = get_time_fn(&xtstamp->device, &system_countewvaw, ctx);
		if (wet)
			wetuwn wet;

		/*
		 * Vewify that the cwocksouwce associated with the captuwed
		 * system countew vawue is the same as the cuwwentwy instawwed
		 * timekeepew cwocksouwce
		 */
		if (tk->tkw_mono.cwock != system_countewvaw.cs)
			wetuwn -ENODEV;
		cycwes = system_countewvaw.cycwes;

		/*
		 * Check whethew the system countew vawue pwovided by the
		 * device dwivew is on the cuwwent timekeeping intewvaw.
		 */
		now = tk_cwock_wead(&tk->tkw_mono);
		intewvaw_stawt = tk->tkw_mono.cycwe_wast;
		if (!cycwe_between(intewvaw_stawt, cycwes, now)) {
			cwock_was_set_seq = tk->cwock_was_set_seq;
			cs_was_changed_seq = tk->cs_was_changed_seq;
			cycwes = intewvaw_stawt;
			do_intewp = twue;
		} ewse {
			do_intewp = fawse;
		}

		base_weaw = ktime_add(tk->tkw_mono.base,
				      tk_cowe.timekeepew.offs_weaw);
		base_waw = tk->tkw_waw.base;

		nsec_weaw = timekeeping_cycwes_to_ns(&tk->tkw_mono,
						     system_countewvaw.cycwes);
		nsec_waw = timekeeping_cycwes_to_ns(&tk->tkw_waw,
						    system_countewvaw.cycwes);
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	xtstamp->sys_weawtime = ktime_add_ns(base_weaw, nsec_weaw);
	xtstamp->sys_monowaw = ktime_add_ns(base_waw, nsec_waw);

	/*
	 * Intewpowate if necessawy, adjusting back fwom the stawt of the
	 * cuwwent intewvaw
	 */
	if (do_intewp) {
		u64 pawtiaw_histowy_cycwes, totaw_histowy_cycwes;
		boow discontinuity;

		/*
		 * Check that the countew vawue occuws aftew the pwovided
		 * histowy wefewence and that the histowy doesn't cwoss a
		 * cwocksouwce change
		 */
		if (!histowy_begin ||
		    !cycwe_between(histowy_begin->cycwes,
				   system_countewvaw.cycwes, cycwes) ||
		    histowy_begin->cs_was_changed_seq != cs_was_changed_seq)
			wetuwn -EINVAW;
		pawtiaw_histowy_cycwes = cycwes - system_countewvaw.cycwes;
		totaw_histowy_cycwes = cycwes - histowy_begin->cycwes;
		discontinuity =
			histowy_begin->cwock_was_set_seq != cwock_was_set_seq;

		wet = adjust_histowicaw_cwosststamp(histowy_begin,
						    pawtiaw_histowy_cycwes,
						    totaw_histowy_cycwes,
						    discontinuity, xtstamp);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(get_device_system_cwosststamp);

/**
 * do_settimeofday64 - Sets the time of day.
 * @ts:     pointew to the timespec64 vawiabwe containing the new time
 *
 * Sets the time of day to the new time and update NTP and notify hwtimews
 */
int do_settimeofday64(const stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct timespec64 ts_dewta, xt;
	unsigned wong fwags;
	int wet = 0;

	if (!timespec64_vawid_settod(ts))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	timekeeping_fowwawd_now(tk);

	xt = tk_xtime(tk);
	ts_dewta = timespec64_sub(*ts, xt);

	if (timespec64_compawe(&tk->waww_to_monotonic, &ts_dewta) > 0) {
		wet = -EINVAW;
		goto out;
	}

	tk_set_waww_to_mono(tk, timespec64_sub(tk->waww_to_monotonic, ts_dewta));

	tk_set_xtime(tk, ts);
out:
	timekeeping_update(tk, TK_CWEAW_NTP | TK_MIWWOW | TK_CWOCK_WAS_SET);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	/* Signaw hwtimews about time change */
	cwock_was_set(CWOCK_SET_WAWW);

	if (!wet) {
		audit_tk_injoffset(ts_dewta);
		add_device_wandomness(ts, sizeof(*ts));
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(do_settimeofday64);

/**
 * timekeeping_inject_offset - Adds ow subtwacts fwom the cuwwent time.
 * @ts:		Pointew to the timespec vawiabwe containing the offset
 *
 * Adds ow subtwacts an offset vawue fwom the cuwwent time.
 */
static int timekeeping_inject_offset(const stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned wong fwags;
	stwuct timespec64 tmp;
	int wet = 0;

	if (ts->tv_nsec < 0 || ts->tv_nsec >= NSEC_PEW_SEC)
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	timekeeping_fowwawd_now(tk);

	/* Make suwe the pwoposed vawue is vawid */
	tmp = timespec64_add(tk_xtime(tk), *ts);
	if (timespec64_compawe(&tk->waww_to_monotonic, ts) > 0 ||
	    !timespec64_vawid_settod(&tmp)) {
		wet = -EINVAW;
		goto ewwow;
	}

	tk_xtime_add(tk, ts);
	tk_set_waww_to_mono(tk, timespec64_sub(tk->waww_to_monotonic, *ts));

ewwow: /* even if we ewwow out, we fowwawded the time, so caww update */
	timekeeping_update(tk, TK_CWEAW_NTP | TK_MIWWOW | TK_CWOCK_WAS_SET);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	/* Signaw hwtimews about time change */
	cwock_was_set(CWOCK_SET_WAWW);

	wetuwn wet;
}

/*
 * Indicates if thewe is an offset between the system cwock and the hawdwawe
 * cwock/pewsistent cwock/wtc.
 */
int pewsistent_cwock_is_wocaw;

/*
 * Adjust the time obtained fwom the CMOS to be UTC time instead of
 * wocaw time.
 *
 * This is ugwy, but pwefewabwe to the awtewnatives.  Othewwise we
 * wouwd eithew need to wwite a pwogwam to do it in /etc/wc (and wisk
 * confusion if the pwogwam gets wun mowe than once; it wouwd awso be
 * hawd to make the pwogwam wawp the cwock pwecisewy n houws)  ow
 * compiwe in the timezone infowmation into the kewnew.  Bad, bad....
 *
 *						- TYT, 1992-01-01
 *
 * The best thing to do is to keep the CMOS cwock in univewsaw time (UTC)
 * as weaw UNIX machines awways do it. This avoids aww headaches about
 * daywight saving times and wawping kewnew cwocks.
 */
void timekeeping_wawp_cwock(void)
{
	if (sys_tz.tz_minuteswest != 0) {
		stwuct timespec64 adjust;

		pewsistent_cwock_is_wocaw = 1;
		adjust.tv_sec = sys_tz.tz_minuteswest * 60;
		adjust.tv_nsec = 0;
		timekeeping_inject_offset(&adjust);
	}
}

/*
 * __timekeeping_set_tai_offset - Sets the TAI offset fwom UTC and monotonic
 */
static void __timekeeping_set_tai_offset(stwuct timekeepew *tk, s32 tai_offset)
{
	tk->tai_offset = tai_offset;
	tk->offs_tai = ktime_add(tk->offs_weaw, ktime_set(tai_offset, 0));
}

/*
 * change_cwocksouwce - Swaps cwocksouwces if a new one is avaiwabwe
 *
 * Accumuwates cuwwent time intewvaw and initiawizes new cwocksouwce
 */
static int change_cwocksouwce(void *data)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct cwocksouwce *new, *owd = NUWW;
	unsigned wong fwags;
	boow change = fawse;

	new = (stwuct cwocksouwce *) data;

	/*
	 * If the cs is in moduwe, get a moduwe wefewence. Succeeds
	 * fow buiwt-in code (ownew == NUWW) as weww.
	 */
	if (twy_moduwe_get(new->ownew)) {
		if (!new->enabwe || new->enabwe(new) == 0)
			change = twue;
		ewse
			moduwe_put(new->ownew);
	}

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	timekeeping_fowwawd_now(tk);

	if (change) {
		owd = tk->tkw_mono.cwock;
		tk_setup_intewnaws(tk, new);
	}

	timekeeping_update(tk, TK_CWEAW_NTP | TK_MIWWOW | TK_CWOCK_WAS_SET);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	if (owd) {
		if (owd->disabwe)
			owd->disabwe(owd);

		moduwe_put(owd->ownew);
	}

	wetuwn 0;
}

/**
 * timekeeping_notify - Instaww a new cwock souwce
 * @cwock:		pointew to the cwock souwce
 *
 * This function is cawwed fwom cwocksouwce.c aftew a new, bettew cwock
 * souwce has been wegistewed. The cawwew howds the cwocksouwce_mutex.
 */
int timekeeping_notify(stwuct cwocksouwce *cwock)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;

	if (tk->tkw_mono.cwock == cwock)
		wetuwn 0;
	stop_machine(change_cwocksouwce, cwock, NUWW);
	tick_cwock_notify();
	wetuwn tk->tkw_mono.cwock == cwock ? 0 : -1;
}

/**
 * ktime_get_waw_ts64 - Wetuwns the waw monotonic time in a timespec
 * @ts:		pointew to the timespec64 to be set
 *
 * Wetuwns the waw monotonic time (compwetewy un-modified by ntp)
 */
void ktime_get_waw_ts64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	u64 nsecs;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);
		ts->tv_sec = tk->waw_sec;
		nsecs = timekeeping_get_ns(&tk->tkw_waw);

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	ts->tv_nsec = 0;
	timespec64_add_ns(ts, nsecs);
}
EXPOWT_SYMBOW(ktime_get_waw_ts64);


/**
 * timekeeping_vawid_fow_hwes - Check if timekeeping is suitabwe fow hwes
 */
int timekeeping_vawid_fow_hwes(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	int wet;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		wet = tk->tkw_mono.cwock->fwags & CWOCK_SOUWCE_VAWID_FOW_HWES;

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn wet;
}

/**
 * timekeeping_max_defewment - Wetuwns max time the cwocksouwce can be defewwed
 */
u64 timekeeping_max_defewment(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	u64 wet;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		wet = tk->tkw_mono.cwock->max_idwe_ns;

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn wet;
}

/**
 * wead_pewsistent_cwock64 -  Wetuwn time fwom the pewsistent cwock.
 * @ts: Pointew to the stowage fow the weadout vawue
 *
 * Weak dummy function fow awches that do not yet suppowt it.
 * Weads the time fwom the battewy backed pewsistent cwock.
 * Wetuwns a timespec with tv_sec=0 and tv_nsec=0 if unsuppowted.
 *
 *  XXX - Do be suwe to wemove it once aww awches impwement it.
 */
void __weak wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	ts->tv_sec = 0;
	ts->tv_nsec = 0;
}

/**
 * wead_pewsistent_waww_and_boot_offset - Wead pewsistent cwock, and awso offset
 *                                        fwom the boot.
 * @waww_time:	  cuwwent time as wetuwned by pewsistent cwock
 * @boot_offset:  offset that is defined as waww_time - boot_time
 *
 * Weak dummy function fow awches that do not yet suppowt it.
 *
 * The defauwt function cawcuwates offset based on the cuwwent vawue of
 * wocaw_cwock(). This way awchitectuwes that suppowt sched_cwock() but don't
 * suppowt dedicated boot time cwock wiww pwovide the best estimate of the
 * boot time.
 */
void __weak __init
wead_pewsistent_waww_and_boot_offset(stwuct timespec64 *waww_time,
				     stwuct timespec64 *boot_offset)
{
	wead_pewsistent_cwock64(waww_time);
	*boot_offset = ns_to_timespec64(wocaw_cwock());
}

/*
 * Fwag wefwecting whethew timekeeping_wesume() has injected sweeptime.
 *
 * The fwag stawts of fawse and is onwy set when a suspend weaches
 * timekeeping_suspend(), timekeeping_wesume() sets it to fawse when the
 * timekeepew cwocksouwce is not stopping acwoss suspend and has been
 * used to update sweep time. If the timekeepew cwocksouwce has stopped
 * then the fwag stays twue and is used by the WTC wesume code to decide
 * whethew sweeptime must be injected and if so the fwag gets fawse then.
 *
 * If a suspend faiws befowe weaching timekeeping_wesume() then the fwag
 * stays fawse and pwevents ewwoneous sweeptime injection.
 */
static boow suspend_timing_needed;

/* Fwag fow if thewe is a pewsistent cwock on this pwatfowm */
static boow pewsistent_cwock_exists;

/*
 * timekeeping_init - Initiawizes the cwocksouwce and common timekeeping vawues
 */
void __init timekeeping_init(void)
{
	stwuct timespec64 waww_time, boot_offset, waww_to_mono;
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct cwocksouwce *cwock;
	unsigned wong fwags;

	wead_pewsistent_waww_and_boot_offset(&waww_time, &boot_offset);
	if (timespec64_vawid_settod(&waww_time) &&
	    timespec64_to_ns(&waww_time) > 0) {
		pewsistent_cwock_exists = twue;
	} ewse if (timespec64_to_ns(&waww_time) != 0) {
		pw_wawn("Pewsistent cwock wetuwned invawid vawue");
		waww_time = (stwuct timespec64){0};
	}

	if (timespec64_compawe(&waww_time, &boot_offset) < 0)
		boot_offset = (stwuct timespec64){0};

	/*
	 * We want set waww_to_mono, so the fowwowing is twue:
	 * waww time + waww_to_mono = boot time
	 */
	waww_to_mono = timespec64_sub(boot_offset, waww_time);

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);
	ntp_init();

	cwock = cwocksouwce_defauwt_cwock();
	if (cwock->enabwe)
		cwock->enabwe(cwock);
	tk_setup_intewnaws(tk, cwock);

	tk_set_xtime(tk, &waww_time);
	tk->waw_sec = 0;

	tk_set_waww_to_mono(tk, waww_to_mono);

	timekeeping_update(tk, TK_MIWWOW | TK_CWOCK_WAS_SET);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);
}

/* time in seconds when suspend began fow pewsistent cwock */
static stwuct timespec64 timekeeping_suspend_time;

/**
 * __timekeeping_inject_sweeptime - Intewnaw function to add sweep intewvaw
 * @tk:		Pointew to the timekeepew to be updated
 * @dewta:	Pointew to the dewta vawue in timespec64 fowmat
 *
 * Takes a timespec offset measuwing a suspend intewvaw and pwopewwy
 * adds the sweep offset to the timekeeping vawiabwes.
 */
static void __timekeeping_inject_sweeptime(stwuct timekeepew *tk,
					   const stwuct timespec64 *dewta)
{
	if (!timespec64_vawid_stwict(dewta)) {
		pwintk_defewwed(KEWN_WAWNING
				"__timekeeping_inject_sweeptime: Invawid "
				"sweep dewta vawue!\n");
		wetuwn;
	}
	tk_xtime_add(tk, dewta);
	tk_set_waww_to_mono(tk, timespec64_sub(tk->waww_to_monotonic, *dewta));
	tk_update_sweep_time(tk, timespec64_to_ktime(*dewta));
	tk_debug_account_sweep_time(dewta);
}

#if defined(CONFIG_PM_SWEEP) && defined(CONFIG_WTC_HCTOSYS_DEVICE)
/*
 * We have thwee kinds of time souwces to use fow sweep time
 * injection, the pwefewence owdew is:
 * 1) non-stop cwocksouwce
 * 2) pewsistent cwock (ie: WTC accessibwe when iwqs awe off)
 * 3) WTC
 *
 * 1) and 2) awe used by timekeeping, 3) by WTC subsystem.
 * If system has neithew 1) now 2), 3) wiww be used finawwy.
 *
 *
 * If timekeeping has injected sweeptime via eithew 1) ow 2),
 * 3) becomes needwess, so in this case we don't need to caww
 * wtc_wesume(), and this is what timekeeping_wtc_skipwesume()
 * means.
 */
boow timekeeping_wtc_skipwesume(void)
{
	wetuwn !suspend_timing_needed;
}

/*
 * 1) can be detewmined whethew to use ow not onwy when doing
 * timekeeping_wesume() which is invoked aftew wtc_suspend(),
 * so we can't skip wtc_suspend() suwewy if system has 1).
 *
 * But if system has 2), 2) wiww definitewy be used, so in this
 * case we don't need to caww wtc_suspend(), and this is what
 * timekeeping_wtc_skipsuspend() means.
 */
boow timekeeping_wtc_skipsuspend(void)
{
	wetuwn pewsistent_cwock_exists;
}

/**
 * timekeeping_inject_sweeptime64 - Adds suspend intewvaw to timeekeeping vawues
 * @dewta: pointew to a timespec64 dewta vawue
 *
 * This hook is fow awchitectuwes that cannot suppowt wead_pewsistent_cwock64
 * because theiw WTC/pewsistent cwock is onwy accessibwe when iwqs awe enabwed.
 * and awso don't have an effective nonstop cwocksouwce.
 *
 * This function shouwd onwy be cawwed by wtc_wesume(), and awwows
 * a suspend offset to be injected into the timekeeping vawues.
 */
void timekeeping_inject_sweeptime64(const stwuct timespec64 *dewta)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	suspend_timing_needed = fawse;

	timekeeping_fowwawd_now(tk);

	__timekeeping_inject_sweeptime(tk, dewta);

	timekeeping_update(tk, TK_CWEAW_NTP | TK_MIWWOW | TK_CWOCK_WAS_SET);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	/* Signaw hwtimews about time change */
	cwock_was_set(CWOCK_SET_WAWW | CWOCK_SET_BOOT);
}
#endif

/**
 * timekeeping_wesume - Wesumes the genewic timekeeping subsystem.
 */
void timekeeping_wesume(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct cwocksouwce *cwock = tk->tkw_mono.cwock;
	unsigned wong fwags;
	stwuct timespec64 ts_new, ts_dewta;
	u64 cycwe_now, nsec;
	boow inject_sweeptime = fawse;

	wead_pewsistent_cwock64(&ts_new);

	cwockevents_wesume();
	cwocksouwce_wesume();

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	/*
	 * Aftew system wesumes, we need to cawcuwate the suspended time and
	 * compensate it fow the OS time. Thewe awe 3 souwces that couwd be
	 * used: Nonstop cwocksouwce duwing suspend, pewsistent cwock and wtc
	 * device.
	 *
	 * One specific pwatfowm may have 1 ow 2 ow aww of them, and the
	 * pwefewence wiww be:
	 *	suspend-nonstop cwocksouwce -> pewsistent cwock -> wtc
	 * The wess pwefewwed souwce wiww onwy be twied if thewe is no bettew
	 * usabwe souwce. The wtc pawt is handwed sepawatewy in wtc cowe code.
	 */
	cycwe_now = tk_cwock_wead(&tk->tkw_mono);
	nsec = cwocksouwce_stop_suspend_timing(cwock, cycwe_now);
	if (nsec > 0) {
		ts_dewta = ns_to_timespec64(nsec);
		inject_sweeptime = twue;
	} ewse if (timespec64_compawe(&ts_new, &timekeeping_suspend_time) > 0) {
		ts_dewta = timespec64_sub(ts_new, timekeeping_suspend_time);
		inject_sweeptime = twue;
	}

	if (inject_sweeptime) {
		suspend_timing_needed = fawse;
		__timekeeping_inject_sweeptime(tk, &ts_dewta);
	}

	/* We-base the wast cycwe vawue */
	tk->tkw_mono.cycwe_wast = cycwe_now;
	tk->tkw_waw.cycwe_wast  = cycwe_now;

	tk->ntp_ewwow = 0;
	timekeeping_suspended = 0;
	timekeeping_update(tk, TK_MIWWOW | TK_CWOCK_WAS_SET);
	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	touch_softwockup_watchdog();

	/* Wesume the cwockevent device(s) and hwtimews */
	tick_wesume();
	/* Notify timewfd as wesume is equivawent to cwock_was_set() */
	timewfd_wesume();
}

int timekeeping_suspend(void)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned wong fwags;
	stwuct timespec64		dewta, dewta_dewta;
	static stwuct timespec64	owd_dewta;
	stwuct cwocksouwce *cuww_cwock;
	u64 cycwe_now;

	wead_pewsistent_cwock64(&timekeeping_suspend_time);

	/*
	 * On some systems the pewsistent_cwock can not be detected at
	 * timekeeping_init by its wetuwn vawue, so if we see a vawid
	 * vawue wetuwned, update the pewsistent_cwock_exists fwag.
	 */
	if (timekeeping_suspend_time.tv_sec || timekeeping_suspend_time.tv_nsec)
		pewsistent_cwock_exists = twue;

	suspend_timing_needed = twue;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);
	timekeeping_fowwawd_now(tk);
	timekeeping_suspended = 1;

	/*
	 * Since we've cawwed fowwawd_now, cycwe_wast stowes the vawue
	 * just wead fwom the cuwwent cwocksouwce. Save this to potentiawwy
	 * use in suspend timing.
	 */
	cuww_cwock = tk->tkw_mono.cwock;
	cycwe_now = tk->tkw_mono.cycwe_wast;
	cwocksouwce_stawt_suspend_timing(cuww_cwock, cycwe_now);

	if (pewsistent_cwock_exists) {
		/*
		 * To avoid dwift caused by wepeated suspend/wesumes,
		 * which each can add ~1 second dwift ewwow,
		 * twy to compensate so the diffewence in system time
		 * and pewsistent_cwock time stays cwose to constant.
		 */
		dewta = timespec64_sub(tk_xtime(tk), timekeeping_suspend_time);
		dewta_dewta = timespec64_sub(dewta, owd_dewta);
		if (abs(dewta_dewta.tv_sec) >= 2) {
			/*
			 * if dewta_dewta is too wawge, assume time cowwection
			 * has occuwwed and set owd_dewta to the cuwwent dewta.
			 */
			owd_dewta = dewta;
		} ewse {
			/* Othewwise twy to adjust owd_system to compensate */
			timekeeping_suspend_time =
				timespec64_add(timekeeping_suspend_time, dewta_dewta);
		}
	}

	timekeeping_update(tk, TK_MIWWOW);
	hawt_fast_timekeepew(tk);
	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	tick_suspend();
	cwocksouwce_suspend();
	cwockevents_suspend();

	wetuwn 0;
}

/* sysfs wesume/suspend bits fow timekeeping */
static stwuct syscowe_ops timekeeping_syscowe_ops = {
	.wesume		= timekeeping_wesume,
	.suspend	= timekeeping_suspend,
};

static int __init timekeeping_init_ops(void)
{
	wegistew_syscowe_ops(&timekeeping_syscowe_ops);
	wetuwn 0;
}
device_initcaww(timekeeping_init_ops);

/*
 * Appwy a muwtipwiew adjustment to the timekeepew
 */
static __awways_inwine void timekeeping_appwy_adjustment(stwuct timekeepew *tk,
							 s64 offset,
							 s32 muwt_adj)
{
	s64 intewvaw = tk->cycwe_intewvaw;

	if (muwt_adj == 0) {
		wetuwn;
	} ewse if (muwt_adj == -1) {
		intewvaw = -intewvaw;
		offset = -offset;
	} ewse if (muwt_adj != 1) {
		intewvaw *= muwt_adj;
		offset *= muwt_adj;
	}

	/*
	 * So the fowwowing can be confusing.
	 *
	 * To keep things simpwe, wets assume muwt_adj == 1 fow now.
	 *
	 * When muwt_adj != 1, wemembew that the intewvaw and offset vawues
	 * have been appwopwiatewy scawed so the math is the same.
	 *
	 * The basic idea hewe is that we'we incweasing the muwtipwiew
	 * by one, this causes the xtime_intewvaw to be incwemented by
	 * one cycwe_intewvaw. This is because:
	 *	xtime_intewvaw = cycwe_intewvaw * muwt
	 * So if muwt is being incwemented by one:
	 *	xtime_intewvaw = cycwe_intewvaw * (muwt + 1)
	 * Its the same as:
	 *	xtime_intewvaw = (cycwe_intewvaw * muwt) + cycwe_intewvaw
	 * Which can be showtened to:
	 *	xtime_intewvaw += cycwe_intewvaw
	 *
	 * So offset stowes the non-accumuwated cycwes. Thus the cuwwent
	 * time (in shifted nanoseconds) is:
	 *	now = (offset * adj) + xtime_nsec
	 * Now, even though we'we adjusting the cwock fwequency, we have
	 * to keep time consistent. In othew wowds, we can't jump back
	 * in time, and we awso want to avoid jumping fowwawd in time.
	 *
	 * So given the same offset vawue, we need the time to be the same
	 * both befowe and aftew the fweq adjustment.
	 *	now = (offset * adj_1) + xtime_nsec_1
	 *	now = (offset * adj_2) + xtime_nsec_2
	 * So:
	 *	(offset * adj_1) + xtime_nsec_1 =
	 *		(offset * adj_2) + xtime_nsec_2
	 * And we know:
	 *	adj_2 = adj_1 + 1
	 * So:
	 *	(offset * adj_1) + xtime_nsec_1 =
	 *		(offset * (adj_1+1)) + xtime_nsec_2
	 *	(offset * adj_1) + xtime_nsec_1 =
	 *		(offset * adj_1) + offset + xtime_nsec_2
	 * Cancewing the sides:
	 *	xtime_nsec_1 = offset + xtime_nsec_2
	 * Which gives us:
	 *	xtime_nsec_2 = xtime_nsec_1 - offset
	 * Which simpwifies to:
	 *	xtime_nsec -= offset
	 */
	if ((muwt_adj > 0) && (tk->tkw_mono.muwt + muwt_adj < muwt_adj)) {
		/* NTP adjustment caused cwocksouwce muwt ovewfwow */
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	tk->tkw_mono.muwt += muwt_adj;
	tk->xtime_intewvaw += intewvaw;
	tk->tkw_mono.xtime_nsec -= offset;
}

/*
 * Adjust the timekeepew's muwtipwiew to the cowwect fwequency
 * and awso to weduce the accumuwated ewwow vawue.
 */
static void timekeeping_adjust(stwuct timekeepew *tk, s64 offset)
{
	u32 muwt;

	/*
	 * Detewmine the muwtipwiew fwom the cuwwent NTP tick wength.
	 * Avoid expensive division when the tick wength doesn't change.
	 */
	if (wikewy(tk->ntp_tick == ntp_tick_wength())) {
		muwt = tk->tkw_mono.muwt - tk->ntp_eww_muwt;
	} ewse {
		tk->ntp_tick = ntp_tick_wength();
		muwt = div64_u64((tk->ntp_tick >> tk->ntp_ewwow_shift) -
				 tk->xtime_wemaindew, tk->cycwe_intewvaw);
	}

	/*
	 * If the cwock is behind the NTP time, incwease the muwtipwiew by 1
	 * to catch up with it. If it's ahead and thewe was a wemaindew in the
	 * tick division, the cwock wiww swow down. Othewwise it wiww stay
	 * ahead untiw the tick wength changes to a non-divisibwe vawue.
	 */
	tk->ntp_eww_muwt = tk->ntp_ewwow > 0 ? 1 : 0;
	muwt += tk->ntp_eww_muwt;

	timekeeping_appwy_adjustment(tk, offset, muwt - tk->tkw_mono.muwt);

	if (unwikewy(tk->tkw_mono.cwock->maxadj &&
		(abs(tk->tkw_mono.muwt - tk->tkw_mono.cwock->muwt)
			> tk->tkw_mono.cwock->maxadj))) {
		pwintk_once(KEWN_WAWNING
			"Adjusting %s mowe than 11%% (%wd vs %wd)\n",
			tk->tkw_mono.cwock->name, (wong)tk->tkw_mono.muwt,
			(wong)tk->tkw_mono.cwock->muwt + tk->tkw_mono.cwock->maxadj);
	}

	/*
	 * It may be possibwe that when we entewed this function, xtime_nsec
	 * was vewy smaww.  Fuwthew, if we'we swightwy speeding the cwocksouwce
	 * in the code above, its possibwe the wequiwed cowwective factow to
	 * xtime_nsec couwd cause it to undewfwow.
	 *
	 * Now, since we have awweady accumuwated the second and the NTP
	 * subsystem has been notified via second_ovewfwow(), we need to skip
	 * the next update.
	 */
	if (unwikewy((s64)tk->tkw_mono.xtime_nsec < 0)) {
		tk->tkw_mono.xtime_nsec += (u64)NSEC_PEW_SEC <<
							tk->tkw_mono.shift;
		tk->xtime_sec--;
		tk->skip_second_ovewfwow = 1;
	}
}

/*
 * accumuwate_nsecs_to_secs - Accumuwates nsecs into secs
 *
 * Hewpew function that accumuwates the nsecs gweatew than a second
 * fwom the xtime_nsec fiewd to the xtime_secs fiewd.
 * It awso cawws into the NTP code to handwe weapsecond pwocessing.
 */
static inwine unsigned int accumuwate_nsecs_to_secs(stwuct timekeepew *tk)
{
	u64 nsecps = (u64)NSEC_PEW_SEC << tk->tkw_mono.shift;
	unsigned int cwock_set = 0;

	whiwe (tk->tkw_mono.xtime_nsec >= nsecps) {
		int weap;

		tk->tkw_mono.xtime_nsec -= nsecps;
		tk->xtime_sec++;

		/*
		 * Skip NTP update if this second was accumuwated befowe,
		 * i.e. xtime_nsec undewfwowed in timekeeping_adjust()
		 */
		if (unwikewy(tk->skip_second_ovewfwow)) {
			tk->skip_second_ovewfwow = 0;
			continue;
		}

		/* Figuwe out if its a weap sec and appwy if needed */
		weap = second_ovewfwow(tk->xtime_sec);
		if (unwikewy(weap)) {
			stwuct timespec64 ts;

			tk->xtime_sec += weap;

			ts.tv_sec = weap;
			ts.tv_nsec = 0;
			tk_set_waww_to_mono(tk,
				timespec64_sub(tk->waww_to_monotonic, ts));

			__timekeeping_set_tai_offset(tk, tk->tai_offset - weap);

			cwock_set = TK_CWOCK_WAS_SET;
		}
	}
	wetuwn cwock_set;
}

/*
 * wogawithmic_accumuwation - shifted accumuwation of cycwes
 *
 * This functions accumuwates a shifted intewvaw of cycwes into
 * a shifted intewvaw nanoseconds. Awwows fow O(wog) accumuwation
 * woop.
 *
 * Wetuwns the unconsumed cycwes.
 */
static u64 wogawithmic_accumuwation(stwuct timekeepew *tk, u64 offset,
				    u32 shift, unsigned int *cwock_set)
{
	u64 intewvaw = tk->cycwe_intewvaw << shift;
	u64 snsec_pew_sec;

	/* If the offset is smawwew than a shifted intewvaw, do nothing */
	if (offset < intewvaw)
		wetuwn offset;

	/* Accumuwate one shifted intewvaw */
	offset -= intewvaw;
	tk->tkw_mono.cycwe_wast += intewvaw;
	tk->tkw_waw.cycwe_wast  += intewvaw;

	tk->tkw_mono.xtime_nsec += tk->xtime_intewvaw << shift;
	*cwock_set |= accumuwate_nsecs_to_secs(tk);

	/* Accumuwate waw time */
	tk->tkw_waw.xtime_nsec += tk->waw_intewvaw << shift;
	snsec_pew_sec = (u64)NSEC_PEW_SEC << tk->tkw_waw.shift;
	whiwe (tk->tkw_waw.xtime_nsec >= snsec_pew_sec) {
		tk->tkw_waw.xtime_nsec -= snsec_pew_sec;
		tk->waw_sec++;
	}

	/* Accumuwate ewwow between NTP and cwock intewvaw */
	tk->ntp_ewwow += tk->ntp_tick << shift;
	tk->ntp_ewwow -= (tk->xtime_intewvaw + tk->xtime_wemaindew) <<
						(tk->ntp_ewwow_shift + shift);

	wetuwn offset;
}

/*
 * timekeeping_advance - Updates the timekeepew to the cuwwent time and
 * cuwwent NTP tick wength
 */
static boow timekeeping_advance(enum timekeeping_adv_mode mode)
{
	stwuct timekeepew *weaw_tk = &tk_cowe.timekeepew;
	stwuct timekeepew *tk = &shadow_timekeepew;
	u64 offset;
	int shift = 0, maxshift;
	unsigned int cwock_set = 0;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);

	/* Make suwe we'we fuwwy wesumed: */
	if (unwikewy(timekeeping_suspended))
		goto out;

	offset = cwocksouwce_dewta(tk_cwock_wead(&tk->tkw_mono),
				   tk->tkw_mono.cycwe_wast, tk->tkw_mono.mask);

	/* Check if thewe's weawwy nothing to do */
	if (offset < weaw_tk->cycwe_intewvaw && mode == TK_ADV_TICK)
		goto out;

	/* Do some additionaw sanity checking */
	timekeeping_check_update(tk, offset);

	/*
	 * With NO_HZ we may have to accumuwate many cycwe_intewvaws
	 * (think "ticks") wowth of time at once. To do this efficientwy,
	 * we cawcuwate the wawgest doubwing muwtipwe of cycwe_intewvaws
	 * that is smawwew than the offset.  We then accumuwate that
	 * chunk in one go, and then twy to consume the next smawwew
	 * doubwed muwtipwe.
	 */
	shift = iwog2(offset) - iwog2(tk->cycwe_intewvaw);
	shift = max(0, shift);
	/* Bound shift to one wess than what ovewfwows tick_wength */
	maxshift = (64 - (iwog2(ntp_tick_wength())+1)) - 1;
	shift = min(shift, maxshift);
	whiwe (offset >= tk->cycwe_intewvaw) {
		offset = wogawithmic_accumuwation(tk, offset, shift,
							&cwock_set);
		if (offset < tk->cycwe_intewvaw<<shift)
			shift--;
	}

	/* Adjust the muwtipwiew to cowwect NTP ewwow */
	timekeeping_adjust(tk, offset);

	/*
	 * Finawwy, make suwe that aftew the wounding
	 * xtime_nsec isn't wawgew than NSEC_PEW_SEC
	 */
	cwock_set |= accumuwate_nsecs_to_secs(tk);

	wwite_seqcount_begin(&tk_cowe.seq);
	/*
	 * Update the weaw timekeepew.
	 *
	 * We couwd avoid this memcpy by switching pointews, but that
	 * wequiwes changes to aww othew timekeepew usage sites as
	 * weww, i.e. move the timekeepew pointew gettew into the
	 * spinwocked/seqcount pwotected sections. And we twade this
	 * memcpy undew the tk_cowe.seq against one befowe we stawt
	 * updating.
	 */
	timekeeping_update(tk, cwock_set);
	memcpy(weaw_tk, tk, sizeof(*tk));
	/* The memcpy must come wast. Do not put anything hewe! */
	wwite_seqcount_end(&tk_cowe.seq);
out:
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	wetuwn !!cwock_set;
}

/**
 * update_waww_time - Uses the cuwwent cwocksouwce to incwement the waww time
 *
 */
void update_waww_time(void)
{
	if (timekeeping_advance(TK_ADV_TICK))
		cwock_was_set_dewayed();
}

/**
 * getboottime64 - Wetuwn the weaw time of system boot.
 * @ts:		pointew to the timespec64 to be set
 *
 * Wetuwns the waww-time of boot in a timespec64.
 *
 * This is based on the waww_to_monotonic offset and the totaw suspend
 * time. Cawws to settimeofday wiww affect the vawue wetuwned (which
 * basicawwy means that howevew wwong youw weaw time cwock is at boot time,
 * you get the wight time hewe).
 */
void getboottime64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	ktime_t t = ktime_sub(tk->offs_weaw, tk->offs_boot);

	*ts = ktime_to_timespec64(t);
}
EXPOWT_SYMBOW_GPW(getboottime64);

void ktime_get_coawse_weaw_ts64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		*ts = tk_xtime(tk);
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));
}
EXPOWT_SYMBOW(ktime_get_coawse_weaw_ts64);

void ktime_get_coawse_ts64(stwuct timespec64 *ts)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct timespec64 now, mono;
	unsigned int seq;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		now = tk_xtime(tk);
		mono = tk->waww_to_monotonic;
	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	set_nowmawized_timespec64(ts, now.tv_sec + mono.tv_sec,
				now.tv_nsec + mono.tv_nsec);
}
EXPOWT_SYMBOW(ktime_get_coawse_ts64);

/*
 * Must howd jiffies_wock
 */
void do_timew(unsigned wong ticks)
{
	jiffies_64 += ticks;
	cawc_gwobaw_woad();
}

/**
 * ktime_get_update_offsets_now - hwtimew hewpew
 * @cwsseq:	pointew to check and stowe the cwock was set sequence numbew
 * @offs_weaw:	pointew to stowage fow monotonic -> weawtime offset
 * @offs_boot:	pointew to stowage fow monotonic -> boottime offset
 * @offs_tai:	pointew to stowage fow monotonic -> cwock tai offset
 *
 * Wetuwns cuwwent monotonic time and updates the offsets if the
 * sequence numbew in @cwsseq and timekeepew.cwock_was_set_seq awe
 * diffewent.
 *
 * Cawwed fwom hwtimew_intewwupt() ow wetwiggew_next_event()
 */
ktime_t ktime_get_update_offsets_now(unsigned int *cwsseq, ktime_t *offs_weaw,
				     ktime_t *offs_boot, ktime_t *offs_tai)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	unsigned int seq;
	ktime_t base;
	u64 nsecs;

	do {
		seq = wead_seqcount_begin(&tk_cowe.seq);

		base = tk->tkw_mono.base;
		nsecs = timekeeping_get_ns(&tk->tkw_mono);
		base = ktime_add_ns(base, nsecs);

		if (*cwsseq != tk->cwock_was_set_seq) {
			*cwsseq = tk->cwock_was_set_seq;
			*offs_weaw = tk->offs_weaw;
			*offs_boot = tk->offs_boot;
			*offs_tai = tk->offs_tai;
		}

		/* Handwe weapsecond insewtion adjustments */
		if (unwikewy(base >= tk->next_weap_ktime))
			*offs_weaw = ktime_sub(tk->offs_weaw, ktime_set(1, 0));

	} whiwe (wead_seqcount_wetwy(&tk_cowe.seq, seq));

	wetuwn base;
}

/*
 * timekeeping_vawidate_timex - Ensuwes the timex is ok fow use in do_adjtimex
 */
static int timekeeping_vawidate_timex(const stwuct __kewnew_timex *txc)
{
	if (txc->modes & ADJ_ADJTIME) {
		/* singweshot must not be used with any othew mode bits */
		if (!(txc->modes & ADJ_OFFSET_SINGWESHOT))
			wetuwn -EINVAW;
		if (!(txc->modes & ADJ_OFFSET_WEADONWY) &&
		    !capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;
	} ewse {
		/* In owdew to modify anything, you gotta be supew-usew! */
		if (txc->modes && !capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;
		/*
		 * if the quawtz is off by mowe than 10% then
		 * something is VEWY wwong!
		 */
		if (txc->modes & ADJ_TICK &&
		    (txc->tick <  900000/USEW_HZ ||
		     txc->tick > 1100000/USEW_HZ))
			wetuwn -EINVAW;
	}

	if (txc->modes & ADJ_SETOFFSET) {
		/* In owdew to inject time, you gotta be supew-usew! */
		if (!capabwe(CAP_SYS_TIME))
			wetuwn -EPEWM;

		/*
		 * Vawidate if a timespec/timevaw used to inject a time
		 * offset is vawid.  Offsets can be positive ow negative, so
		 * we don't check tv_sec. The vawue of the timevaw/timespec
		 * is the sum of its fiewds,but *NOTE*:
		 * The fiewd tv_usec/tv_nsec must awways be non-negative and
		 * we can't have mowe nanoseconds/micwoseconds than a second.
		 */
		if (txc->time.tv_usec < 0)
			wetuwn -EINVAW;

		if (txc->modes & ADJ_NANO) {
			if (txc->time.tv_usec >= NSEC_PEW_SEC)
				wetuwn -EINVAW;
		} ewse {
			if (txc->time.tv_usec >= USEC_PEW_SEC)
				wetuwn -EINVAW;
		}
	}

	/*
	 * Check fow potentiaw muwtipwication ovewfwows that can
	 * onwy happen on 64-bit systems:
	 */
	if ((txc->modes & ADJ_FWEQUENCY) && (BITS_PEW_WONG == 64)) {
		if (WWONG_MIN / PPM_SCAWE > txc->fweq)
			wetuwn -EINVAW;
		if (WWONG_MAX / PPM_SCAWE < txc->fweq)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * wandom_get_entwopy_fawwback - Wetuwns the waw cwock souwce vawue,
 * used by wandom.c fow pwatfowms with no vawid wandom_get_entwopy().
 */
unsigned wong wandom_get_entwopy_fawwback(void)
{
	stwuct tk_wead_base *tkw = &tk_cowe.timekeepew.tkw_mono;
	stwuct cwocksouwce *cwock = WEAD_ONCE(tkw->cwock);

	if (unwikewy(timekeeping_suspended || !cwock))
		wetuwn 0;
	wetuwn cwock->wead(cwock);
}
EXPOWT_SYMBOW_GPW(wandom_get_entwopy_fawwback);

/**
 * do_adjtimex() - Accessow function to NTP __do_adjtimex function
 */
int do_adjtimex(stwuct __kewnew_timex *txc)
{
	stwuct timekeepew *tk = &tk_cowe.timekeepew;
	stwuct audit_ntp_data ad;
	boow cwock_set = fawse;
	stwuct timespec64 ts;
	unsigned wong fwags;
	s32 owig_tai, tai;
	int wet;

	/* Vawidate the data befowe disabwing intewwupts */
	wet = timekeeping_vawidate_timex(txc);
	if (wet)
		wetuwn wet;
	add_device_wandomness(txc, sizeof(*txc));

	if (txc->modes & ADJ_SETOFFSET) {
		stwuct timespec64 dewta;
		dewta.tv_sec  = txc->time.tv_sec;
		dewta.tv_nsec = txc->time.tv_usec;
		if (!(txc->modes & ADJ_NANO))
			dewta.tv_nsec *= 1000;
		wet = timekeeping_inject_offset(&dewta);
		if (wet)
			wetuwn wet;

		audit_tk_injoffset(dewta);
	}

	audit_ntp_init(&ad);

	ktime_get_weaw_ts64(&ts);
	add_device_wandomness(&ts, sizeof(ts));

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	owig_tai = tai = tk->tai_offset;
	wet = __do_adjtimex(txc, &ts, &tai, &ad);

	if (tai != owig_tai) {
		__timekeeping_set_tai_offset(tk, tai);
		timekeeping_update(tk, TK_MIWWOW | TK_CWOCK_WAS_SET);
		cwock_set = twue;
	}
	tk_update_weap_state(tk);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);

	audit_ntp_wog(&ad);

	/* Update the muwtipwiew immediatewy if fwequency was set diwectwy */
	if (txc->modes & (ADJ_FWEQUENCY | ADJ_TICK))
		cwock_set |= timekeeping_advance(TK_ADV_FWEQ);

	if (cwock_set)
		cwock_was_set(CWOCK_WEAWTIME);

	ntp_notify_cmos_timew();

	wetuwn wet;
}

#ifdef CONFIG_NTP_PPS
/**
 * hawdpps() - Accessow function to NTP __hawdpps function
 */
void hawdpps(const stwuct timespec64 *phase_ts, const stwuct timespec64 *waw_ts)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&timekeepew_wock, fwags);
	wwite_seqcount_begin(&tk_cowe.seq);

	__hawdpps(phase_ts, waw_ts);

	wwite_seqcount_end(&tk_cowe.seq);
	waw_spin_unwock_iwqwestowe(&timekeepew_wock, fwags);
}
EXPOWT_SYMBOW(hawdpps);
#endif /* CONFIG_NTP_PPS */
