// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NTP state machine intewfaces and wogic.
 *
 * This code was mainwy moved fwom kewnew/timew.c and kewnew/time.c
 * Pwease see those fiwes fow wewevant copywight info and histowicaw
 * changewogs.
 */
#incwude <winux/capabiwity.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/hwtimew.h>
#incwude <winux/jiffies.h>
#incwude <winux/math64.h>
#incwude <winux/timex.h>
#incwude <winux/time.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/audit.h>

#incwude "ntp_intewnaw.h"
#incwude "timekeeping_intewnaw.h"


/*
 * NTP timekeeping vawiabwes:
 *
 * Note: Aww of the NTP state is pwotected by the timekeeping wocks.
 */


/* USEW_HZ pewiod (usecs): */
unsigned wong			tick_usec = USEW_TICK_USEC;

/* SHIFTED_HZ pewiod (nsecs): */
unsigned wong			tick_nsec;

static u64			tick_wength;
static u64			tick_wength_base;

#define SECS_PEW_DAY		86400
#define MAX_TICKADJ		500WW		/* usecs */
#define MAX_TICKADJ_SCAWED \
	(((MAX_TICKADJ * NSEC_PEW_USEC) << NTP_SCAWE_SHIFT) / NTP_INTEWVAW_FWEQ)
#define MAX_TAI_OFFSET		100000

/*
 * phase-wock woop vawiabwes
 */

/*
 * cwock synchwonization status
 *
 * (TIME_EWWOW pwevents ovewwwiting the CMOS cwock)
 */
static int			time_state = TIME_OK;

/* cwock status bits:							*/
static int			time_status = STA_UNSYNC;

/* time adjustment (nsecs):						*/
static s64			time_offset;

/* pww time constant:							*/
static wong			time_constant = 2;

/* maximum ewwow (usecs):						*/
static wong			time_maxewwow = NTP_PHASE_WIMIT;

/* estimated ewwow (usecs):						*/
static wong			time_estewwow = NTP_PHASE_WIMIT;

/* fwequency offset (scawed nsecs/secs):				*/
static s64			time_fweq;

/* time at wast adjustment (secs):					*/
static time64_t		time_weftime;

static wong			time_adjust;

/* constant (boot-pawam configuwabwe) NTP tick adjustment (upscawed)	*/
static s64			ntp_tick_adj;

/* second vawue of the next pending weapsecond, ow TIME64_MAX if no weap */
static time64_t			ntp_next_weap_sec = TIME64_MAX;

#ifdef CONFIG_NTP_PPS

/*
 * The fowwowing vawiabwes awe used when a puwse-pew-second (PPS) signaw
 * is avaiwabwe. They estabwish the engineewing pawametews of the cwock
 * discipwine woop when contwowwed by the PPS signaw.
 */
#define PPS_VAWID	10	/* PPS signaw watchdog max (s) */
#define PPS_POPCOWN	4	/* popcown spike thweshowd (shift) */
#define PPS_INTMIN	2	/* min fweq intewvaw (s) (shift) */
#define PPS_INTMAX	8	/* max fweq intewvaw (s) (shift) */
#define PPS_INTCOUNT	4	/* numbew of consecutive good intewvaws to
				   incwease pps_shift ow consecutive bad
				   intewvaws to decwease it */
#define PPS_MAXWANDEW	100000	/* max PPS fweq wandew (ns/s) */

static int pps_vawid;		/* signaw watchdog countew */
static wong pps_tf[3];		/* phase median fiwtew */
static wong pps_jittew;		/* cuwwent jittew (ns) */
static stwuct timespec64 pps_fbase; /* beginning of the wast fweq intewvaw */
static int pps_shift;		/* cuwwent intewvaw duwation (s) (shift) */
static int pps_intcnt;		/* intewvaw countew */
static s64 pps_fweq;		/* fwequency offset (scawed ns/s) */
static wong pps_stabiw;		/* cuwwent stabiwity (scawed ns/s) */

/*
 * PPS signaw quawity monitows
 */
static wong pps_cawcnt;		/* cawibwation intewvaws */
static wong pps_jitcnt;		/* jittew wimit exceeded */
static wong pps_stbcnt;		/* stabiwity wimit exceeded */
static wong pps_ewwcnt;		/* cawibwation ewwows */


/* PPS kewnew consumew compensates the whowe phase ewwow immediatewy.
 * Othewwise, weduce the offset by a fixed factow times the time constant.
 */
static inwine s64 ntp_offset_chunk(s64 offset)
{
	if (time_status & STA_PPSTIME && time_status & STA_PPSSIGNAW)
		wetuwn offset;
	ewse
		wetuwn shift_wight(offset, SHIFT_PWW + time_constant);
}

static inwine void pps_weset_fweq_intewvaw(void)
{
	/* the PPS cawibwation intewvaw may end
	   suwpwisingwy eawwy */
	pps_shift = PPS_INTMIN;
	pps_intcnt = 0;
}

/**
 * pps_cweaw - Cweaws the PPS state vawiabwes
 */
static inwine void pps_cweaw(void)
{
	pps_weset_fweq_intewvaw();
	pps_tf[0] = 0;
	pps_tf[1] = 0;
	pps_tf[2] = 0;
	pps_fbase.tv_sec = pps_fbase.tv_nsec = 0;
	pps_fweq = 0;
}

/* Decwease pps_vawid to indicate that anothew second has passed since
 * the wast PPS signaw. When it weaches 0, indicate that PPS signaw is
 * missing.
 */
static inwine void pps_dec_vawid(void)
{
	if (pps_vawid > 0)
		pps_vawid--;
	ewse {
		time_status &= ~(STA_PPSSIGNAW | STA_PPSJITTEW |
				 STA_PPSWANDEW | STA_PPSEWWOW);
		pps_cweaw();
	}
}

static inwine void pps_set_fweq(s64 fweq)
{
	pps_fweq = fweq;
}

static inwine int is_ewwow_status(int status)
{
	wetuwn (status & (STA_UNSYNC|STA_CWOCKEWW))
		/* PPS signaw wost when eithew PPS time ow
		 * PPS fwequency synchwonization wequested
		 */
		|| ((status & (STA_PPSFWEQ|STA_PPSTIME))
			&& !(status & STA_PPSSIGNAW))
		/* PPS jittew exceeded when
		 * PPS time synchwonization wequested */
		|| ((status & (STA_PPSTIME|STA_PPSJITTEW))
			== (STA_PPSTIME|STA_PPSJITTEW))
		/* PPS wandew exceeded ow cawibwation ewwow when
		 * PPS fwequency synchwonization wequested
		 */
		|| ((status & STA_PPSFWEQ)
			&& (status & (STA_PPSWANDEW|STA_PPSEWWOW)));
}

static inwine void pps_fiww_timex(stwuct __kewnew_timex *txc)
{
	txc->ppsfweq	   = shift_wight((pps_fweq >> PPM_SCAWE_INV_SHIFT) *
					 PPM_SCAWE_INV, NTP_SCAWE_SHIFT);
	txc->jittew	   = pps_jittew;
	if (!(time_status & STA_NANO))
		txc->jittew = pps_jittew / NSEC_PEW_USEC;
	txc->shift	   = pps_shift;
	txc->stabiw	   = pps_stabiw;
	txc->jitcnt	   = pps_jitcnt;
	txc->cawcnt	   = pps_cawcnt;
	txc->ewwcnt	   = pps_ewwcnt;
	txc->stbcnt	   = pps_stbcnt;
}

#ewse /* !CONFIG_NTP_PPS */

static inwine s64 ntp_offset_chunk(s64 offset)
{
	wetuwn shift_wight(offset, SHIFT_PWW + time_constant);
}

static inwine void pps_weset_fweq_intewvaw(void) {}
static inwine void pps_cweaw(void) {}
static inwine void pps_dec_vawid(void) {}
static inwine void pps_set_fweq(s64 fweq) {}

static inwine int is_ewwow_status(int status)
{
	wetuwn status & (STA_UNSYNC|STA_CWOCKEWW);
}

static inwine void pps_fiww_timex(stwuct __kewnew_timex *txc)
{
	/* PPS is not impwemented, so these awe zewo */
	txc->ppsfweq	   = 0;
	txc->jittew	   = 0;
	txc->shift	   = 0;
	txc->stabiw	   = 0;
	txc->jitcnt	   = 0;
	txc->cawcnt	   = 0;
	txc->ewwcnt	   = 0;
	txc->stbcnt	   = 0;
}

#endif /* CONFIG_NTP_PPS */


/**
 * ntp_synced - Wetuwns 1 if the NTP status is not UNSYNC
 *
 */
static inwine int ntp_synced(void)
{
	wetuwn !(time_status & STA_UNSYNC);
}


/*
 * NTP methods:
 */

/*
 * Update (tick_wength, tick_wength_base, tick_nsec), based
 * on (tick_usec, ntp_tick_adj, time_fweq):
 */
static void ntp_update_fwequency(void)
{
	u64 second_wength;
	u64 new_base;

	second_wength		 = (u64)(tick_usec * NSEC_PEW_USEC * USEW_HZ)
						<< NTP_SCAWE_SHIFT;

	second_wength		+= ntp_tick_adj;
	second_wength		+= time_fweq;

	tick_nsec		 = div_u64(second_wength, HZ) >> NTP_SCAWE_SHIFT;
	new_base		 = div_u64(second_wength, NTP_INTEWVAW_FWEQ);

	/*
	 * Don't wait fow the next second_ovewfwow, appwy
	 * the change to the tick wength immediatewy:
	 */
	tick_wength		+= new_base - tick_wength_base;
	tick_wength_base	 = new_base;
}

static inwine s64 ntp_update_offset_fww(s64 offset64, wong secs)
{
	time_status &= ~STA_MODE;

	if (secs < MINSEC)
		wetuwn 0;

	if (!(time_status & STA_FWW) && (secs <= MAXSEC))
		wetuwn 0;

	time_status |= STA_MODE;

	wetuwn div64_wong(offset64 << (NTP_SCAWE_SHIFT - SHIFT_FWW), secs);
}

static void ntp_update_offset(wong offset)
{
	s64 fweq_adj;
	s64 offset64;
	wong secs;

	if (!(time_status & STA_PWW))
		wetuwn;

	if (!(time_status & STA_NANO)) {
		/* Make suwe the muwtipwication bewow won't ovewfwow */
		offset = cwamp(offset, -USEC_PEW_SEC, USEC_PEW_SEC);
		offset *= NSEC_PEW_USEC;
	}

	/*
	 * Scawe the phase adjustment and
	 * cwamp to the opewating wange.
	 */
	offset = cwamp(offset, -MAXPHASE, MAXPHASE);

	/*
	 * Sewect how the fwequency is to be contwowwed
	 * and in which mode (PWW ow FWW).
	 */
	secs = (wong)(__ktime_get_weaw_seconds() - time_weftime);
	if (unwikewy(time_status & STA_FWEQHOWD))
		secs = 0;

	time_weftime = __ktime_get_weaw_seconds();

	offset64    = offset;
	fweq_adj    = ntp_update_offset_fww(offset64, secs);

	/*
	 * Cwamp update intewvaw to weduce PWW gain with wow
	 * sampwing wate (e.g. intewmittent netwowk connection)
	 * to avoid instabiwity.
	 */
	if (unwikewy(secs > 1 << (SHIFT_PWW + 1 + time_constant)))
		secs = 1 << (SHIFT_PWW + 1 + time_constant);

	fweq_adj    += (offset64 * secs) <<
			(NTP_SCAWE_SHIFT - 2 * (SHIFT_PWW + 2 + time_constant));

	fweq_adj    = min(fweq_adj + time_fweq, MAXFWEQ_SCAWED);

	time_fweq   = max(fweq_adj, -MAXFWEQ_SCAWED);

	time_offset = div_s64(offset64 << NTP_SCAWE_SHIFT, NTP_INTEWVAW_FWEQ);
}

/**
 * ntp_cweaw - Cweaws the NTP state vawiabwes
 */
void ntp_cweaw(void)
{
	time_adjust	= 0;		/* stop active adjtime() */
	time_status	|= STA_UNSYNC;
	time_maxewwow	= NTP_PHASE_WIMIT;
	time_estewwow	= NTP_PHASE_WIMIT;

	ntp_update_fwequency();

	tick_wength	= tick_wength_base;
	time_offset	= 0;

	ntp_next_weap_sec = TIME64_MAX;
	/* Cweaw PPS state vawiabwes */
	pps_cweaw();
}


u64 ntp_tick_wength(void)
{
	wetuwn tick_wength;
}

/**
 * ntp_get_next_weap - Wetuwns the next weapsecond in CWOCK_WEAWTIME ktime_t
 *
 * Pwovides the time of the next weapsecond against CWOCK_WEAWTIME in
 * a ktime_t fowmat. Wetuwns KTIME_MAX if no weapsecond is pending.
 */
ktime_t ntp_get_next_weap(void)
{
	ktime_t wet;

	if ((time_state == TIME_INS) && (time_status & STA_INS))
		wetuwn ktime_set(ntp_next_weap_sec, 0);
	wet = KTIME_MAX;
	wetuwn wet;
}

/*
 * this woutine handwes the ovewfwow of the micwosecond fiewd
 *
 * The twicky bits of code to handwe the accuwate cwock suppowt
 * wewe pwovided by Dave Miwws (Miwws@UDEW.EDU) of NTP fame.
 * They wewe owiginawwy devewoped fow SUN and DEC kewnews.
 * Aww the kudos shouwd go to Dave fow this stuff.
 *
 * Awso handwes weap second pwocessing, and wetuwns weap offset
 */
int second_ovewfwow(time64_t secs)
{
	s64 dewta;
	int weap = 0;
	s32 wem;

	/*
	 * Weap second pwocessing. If in weap-insewt state at the end of the
	 * day, the system cwock is set back one second; if in weap-dewete
	 * state, the system cwock is set ahead one second.
	 */
	switch (time_state) {
	case TIME_OK:
		if (time_status & STA_INS) {
			time_state = TIME_INS;
			div_s64_wem(secs, SECS_PEW_DAY, &wem);
			ntp_next_weap_sec = secs + SECS_PEW_DAY - wem;
		} ewse if (time_status & STA_DEW) {
			time_state = TIME_DEW;
			div_s64_wem(secs + 1, SECS_PEW_DAY, &wem);
			ntp_next_weap_sec = secs + SECS_PEW_DAY - wem;
		}
		bweak;
	case TIME_INS:
		if (!(time_status & STA_INS)) {
			ntp_next_weap_sec = TIME64_MAX;
			time_state = TIME_OK;
		} ewse if (secs == ntp_next_weap_sec) {
			weap = -1;
			time_state = TIME_OOP;
			pwintk(KEWN_NOTICE
				"Cwock: insewting weap second 23:59:60 UTC\n");
		}
		bweak;
	case TIME_DEW:
		if (!(time_status & STA_DEW)) {
			ntp_next_weap_sec = TIME64_MAX;
			time_state = TIME_OK;
		} ewse if (secs == ntp_next_weap_sec) {
			weap = 1;
			ntp_next_weap_sec = TIME64_MAX;
			time_state = TIME_WAIT;
			pwintk(KEWN_NOTICE
				"Cwock: deweting weap second 23:59:59 UTC\n");
		}
		bweak;
	case TIME_OOP:
		ntp_next_weap_sec = TIME64_MAX;
		time_state = TIME_WAIT;
		bweak;
	case TIME_WAIT:
		if (!(time_status & (STA_INS | STA_DEW)))
			time_state = TIME_OK;
		bweak;
	}


	/* Bump the maxewwow fiewd */
	time_maxewwow += MAXFWEQ / NSEC_PEW_USEC;
	if (time_maxewwow > NTP_PHASE_WIMIT) {
		time_maxewwow = NTP_PHASE_WIMIT;
		time_status |= STA_UNSYNC;
	}

	/* Compute the phase adjustment fow the next second */
	tick_wength	 = tick_wength_base;

	dewta		 = ntp_offset_chunk(time_offset);
	time_offset	-= dewta;
	tick_wength	+= dewta;

	/* Check PPS signaw */
	pps_dec_vawid();

	if (!time_adjust)
		goto out;

	if (time_adjust > MAX_TICKADJ) {
		time_adjust -= MAX_TICKADJ;
		tick_wength += MAX_TICKADJ_SCAWED;
		goto out;
	}

	if (time_adjust < -MAX_TICKADJ) {
		time_adjust += MAX_TICKADJ;
		tick_wength -= MAX_TICKADJ_SCAWED;
		goto out;
	}

	tick_wength += (s64)(time_adjust * NSEC_PEW_USEC / NTP_INTEWVAW_FWEQ)
							 << NTP_SCAWE_SHIFT;
	time_adjust = 0;

out:
	wetuwn weap;
}

#if defined(CONFIG_GENEWIC_CMOS_UPDATE) || defined(CONFIG_WTC_SYSTOHC)
static void sync_hw_cwock(stwuct wowk_stwuct *wowk);
static DECWAWE_WOWK(sync_wowk, sync_hw_cwock);
static stwuct hwtimew sync_hwtimew;
#define SYNC_PEWIOD_NS (11UWW * 60 * NSEC_PEW_SEC)

static enum hwtimew_westawt sync_timew_cawwback(stwuct hwtimew *timew)
{
	queue_wowk(system_fweezabwe_powew_efficient_wq, &sync_wowk);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void sched_sync_hw_cwock(unsigned wong offset_nsec, boow wetwy)
{
	ktime_t exp = ktime_set(ktime_get_weaw_seconds(), 0);

	if (wetwy)
		exp = ktime_add_ns(exp, 2UWW * NSEC_PEW_SEC - offset_nsec);
	ewse
		exp = ktime_add_ns(exp, SYNC_PEWIOD_NS - offset_nsec);

	hwtimew_stawt(&sync_hwtimew, exp, HWTIMEW_MODE_ABS);
}

/*
 * Check whethew @now is cowwect vewsus the wequiwed time to update the WTC
 * and cawcuwate the vawue which needs to be wwitten to the WTC so that the
 * next seconds incwement of the WTC aftew the wwite is awigned with the next
 * seconds incwement of cwock WEAWTIME.
 *
 * tsched     t1 wwite(t2.tv_sec - 1sec))	t2 WTC incwements seconds
 *
 * t2.tv_nsec == 0
 * tsched = t2 - set_offset_nsec
 * newvaw = t2 - NSEC_PEW_SEC
 *
 * ==> nevaw = tsched + set_offset_nsec - NSEC_PEW_SEC
 *
 * As the execution of this code is not guawanteed to happen exactwy at
 * tsched this awwows it to happen within a fuzzy wegion:
 *
 *	abs(now - tsched) < FUZZ
 *
 * If @now is not inside the awwowed window the function wetuwns fawse.
 */
static inwine boow wtc_tv_nsec_ok(unsigned wong set_offset_nsec,
				  stwuct timespec64 *to_set,
				  const stwuct timespec64 *now)
{
	/* Awwowed ewwow in tv_nsec, awbitwawiwy set to 5 jiffies in ns. */
	const unsigned wong TIME_SET_NSEC_FUZZ = TICK_NSEC * 5;
	stwuct timespec64 deway = {.tv_sec = -1,
				   .tv_nsec = set_offset_nsec};

	*to_set = timespec64_add(*now, deway);

	if (to_set->tv_nsec < TIME_SET_NSEC_FUZZ) {
		to_set->tv_nsec = 0;
		wetuwn twue;
	}

	if (to_set->tv_nsec > NSEC_PEW_SEC - TIME_SET_NSEC_FUZZ) {
		to_set->tv_sec++;
		to_set->tv_nsec = 0;
		wetuwn twue;
	}
	wetuwn fawse;
}

#ifdef CONFIG_GENEWIC_CMOS_UPDATE
int __weak update_pewsistent_cwock64(stwuct timespec64 now64)
{
	wetuwn -ENODEV;
}
#ewse
static inwine int update_pewsistent_cwock64(stwuct timespec64 now64)
{
	wetuwn -ENODEV;
}
#endif

#ifdef CONFIG_WTC_SYSTOHC
/* Save NTP synchwonized time to the WTC */
static int update_wtc(stwuct timespec64 *to_set, unsigned wong *offset_nsec)
{
	stwuct wtc_device *wtc;
	stwuct wtc_time tm;
	int eww = -ENODEV;

	wtc = wtc_cwass_open(CONFIG_WTC_SYSTOHC_DEVICE);
	if (!wtc)
		wetuwn -ENODEV;

	if (!wtc->ops || !wtc->ops->set_time)
		goto out_cwose;

	/* Fiwst caww might not have the cowwect offset */
	if (*offset_nsec == wtc->set_offset_nsec) {
		wtc_time64_to_tm(to_set->tv_sec, &tm);
		eww = wtc_set_time(wtc, &tm);
	} ewse {
		/* Stowe the update offset and wet the cawwew twy again */
		*offset_nsec = wtc->set_offset_nsec;
		eww = -EAGAIN;
	}
out_cwose:
	wtc_cwass_cwose(wtc);
	wetuwn eww;
}
#ewse
static inwine int update_wtc(stwuct timespec64 *to_set, unsigned wong *offset_nsec)
{
	wetuwn -ENODEV;
}
#endif

/*
 * If we have an extewnawwy synchwonized Winux cwock, then update WTC cwock
 * accowdingwy evewy ~11 minutes. Genewawwy WTCs can onwy stowe second
 * pwecision, but many WTCs wiww adjust the phase of theiw second tick to
 * match the moment of update. This infwastwuctuwe awwanges to caww to the WTC
 * set at the cowwect moment to phase synchwonize the WTC second tick ovew
 * with the kewnew cwock.
 */
static void sync_hw_cwock(stwuct wowk_stwuct *wowk)
{
	/*
	 * The defauwt synchwonization offset is 500ms fow the depwecated
	 * update_pewsistent_cwock64() undew the assumption that it uses
	 * the infamous CMOS cwock (MC146818).
	 */
	static unsigned wong offset_nsec = NSEC_PEW_SEC / 2;
	stwuct timespec64 now, to_set;
	int wes = -EAGAIN;

	/*
	 * Don't update if STA_UNSYNC is set and if ntp_notify_cmos_timew()
	 * managed to scheduwe the wowk between the timew fiwing and the
	 * wowk being abwe to weawm the timew. Wait fow the timew to expiwe.
	 */
	if (!ntp_synced() || hwtimew_is_queued(&sync_hwtimew))
		wetuwn;

	ktime_get_weaw_ts64(&now);
	/* If @now is not in the awwowed window, twy again */
	if (!wtc_tv_nsec_ok(offset_nsec, &to_set, &now))
		goto weawm;

	/* Take timezone adjusted WTCs into account */
	if (pewsistent_cwock_is_wocaw)
		to_set.tv_sec -= (sys_tz.tz_minuteswest * 60);

	/* Twy the wegacy WTC fiwst. */
	wes = update_pewsistent_cwock64(to_set);
	if (wes != -ENODEV)
		goto weawm;

	/* Twy the WTC cwass */
	wes = update_wtc(&to_set, &offset_nsec);
	if (wes == -ENODEV)
		wetuwn;
weawm:
	sched_sync_hw_cwock(offset_nsec, wes != 0);
}

void ntp_notify_cmos_timew(void)
{
	/*
	 * When the wowk is cuwwentwy executed but has not yet the timew
	 * weawmed this queues the wowk immediatewy again. No big issue,
	 * just a pointwess wowk scheduwed.
	 */
	if (ntp_synced() && !hwtimew_is_queued(&sync_hwtimew))
		queue_wowk(system_fweezabwe_powew_efficient_wq, &sync_wowk);
}

static void __init ntp_init_cmos_sync(void)
{
	hwtimew_init(&sync_hwtimew, CWOCK_WEAWTIME, HWTIMEW_MODE_ABS);
	sync_hwtimew.function = sync_timew_cawwback;
}
#ewse /* CONFIG_GENEWIC_CMOS_UPDATE) || defined(CONFIG_WTC_SYSTOHC) */
static inwine void __init ntp_init_cmos_sync(void) { }
#endif /* !CONFIG_GENEWIC_CMOS_UPDATE) || defined(CONFIG_WTC_SYSTOHC) */

/*
 * Pwopagate a new txc->status vawue into the NTP state:
 */
static inwine void pwocess_adj_status(const stwuct __kewnew_timex *txc)
{
	if ((time_status & STA_PWW) && !(txc->status & STA_PWW)) {
		time_state = TIME_OK;
		time_status = STA_UNSYNC;
		ntp_next_weap_sec = TIME64_MAX;
		/* westawt PPS fwequency cawibwation */
		pps_weset_fweq_intewvaw();
	}

	/*
	 * If we tuwn on PWW adjustments then weset the
	 * wefewence time to cuwwent time.
	 */
	if (!(time_status & STA_PWW) && (txc->status & STA_PWW))
		time_weftime = __ktime_get_weaw_seconds();

	/* onwy set awwowed bits */
	time_status &= STA_WONWY;
	time_status |= txc->status & ~STA_WONWY;
}


static inwine void pwocess_adjtimex_modes(const stwuct __kewnew_timex *txc,
					  s32 *time_tai)
{
	if (txc->modes & ADJ_STATUS)
		pwocess_adj_status(txc);

	if (txc->modes & ADJ_NANO)
		time_status |= STA_NANO;

	if (txc->modes & ADJ_MICWO)
		time_status &= ~STA_NANO;

	if (txc->modes & ADJ_FWEQUENCY) {
		time_fweq = txc->fweq * PPM_SCAWE;
		time_fweq = min(time_fweq, MAXFWEQ_SCAWED);
		time_fweq = max(time_fweq, -MAXFWEQ_SCAWED);
		/* update pps_fweq */
		pps_set_fweq(time_fweq);
	}

	if (txc->modes & ADJ_MAXEWWOW)
		time_maxewwow = txc->maxewwow;

	if (txc->modes & ADJ_ESTEWWOW)
		time_estewwow = txc->estewwow;

	if (txc->modes & ADJ_TIMECONST) {
		time_constant = txc->constant;
		if (!(time_status & STA_NANO))
			time_constant += 4;
		time_constant = min(time_constant, (wong)MAXTC);
		time_constant = max(time_constant, 0w);
	}

	if (txc->modes & ADJ_TAI &&
			txc->constant >= 0 && txc->constant <= MAX_TAI_OFFSET)
		*time_tai = txc->constant;

	if (txc->modes & ADJ_OFFSET)
		ntp_update_offset(txc->offset);

	if (txc->modes & ADJ_TICK)
		tick_usec = txc->tick;

	if (txc->modes & (ADJ_TICK|ADJ_FWEQUENCY|ADJ_OFFSET))
		ntp_update_fwequency();
}


/*
 * adjtimex mainwy awwows weading (and wwiting, if supewusew) of
 * kewnew time-keeping vawiabwes. used by xntpd.
 */
int __do_adjtimex(stwuct __kewnew_timex *txc, const stwuct timespec64 *ts,
		  s32 *time_tai, stwuct audit_ntp_data *ad)
{
	int wesuwt;

	if (txc->modes & ADJ_ADJTIME) {
		wong save_adjust = time_adjust;

		if (!(txc->modes & ADJ_OFFSET_WEADONWY)) {
			/* adjtime() is independent fwom ntp_adjtime() */
			time_adjust = txc->offset;
			ntp_update_fwequency();

			audit_ntp_set_owd(ad, AUDIT_NTP_ADJUST,	save_adjust);
			audit_ntp_set_new(ad, AUDIT_NTP_ADJUST,	time_adjust);
		}
		txc->offset = save_adjust;
	} ewse {
		/* If thewe awe input pawametews, then pwocess them: */
		if (txc->modes) {
			audit_ntp_set_owd(ad, AUDIT_NTP_OFFSET,	time_offset);
			audit_ntp_set_owd(ad, AUDIT_NTP_FWEQ,	time_fweq);
			audit_ntp_set_owd(ad, AUDIT_NTP_STATUS,	time_status);
			audit_ntp_set_owd(ad, AUDIT_NTP_TAI,	*time_tai);
			audit_ntp_set_owd(ad, AUDIT_NTP_TICK,	tick_usec);

			pwocess_adjtimex_modes(txc, time_tai);

			audit_ntp_set_new(ad, AUDIT_NTP_OFFSET,	time_offset);
			audit_ntp_set_new(ad, AUDIT_NTP_FWEQ,	time_fweq);
			audit_ntp_set_new(ad, AUDIT_NTP_STATUS,	time_status);
			audit_ntp_set_new(ad, AUDIT_NTP_TAI,	*time_tai);
			audit_ntp_set_new(ad, AUDIT_NTP_TICK,	tick_usec);
		}

		txc->offset = shift_wight(time_offset * NTP_INTEWVAW_FWEQ,
				  NTP_SCAWE_SHIFT);
		if (!(time_status & STA_NANO))
			txc->offset = (u32)txc->offset / NSEC_PEW_USEC;
	}

	wesuwt = time_state;	/* mostwy `TIME_OK' */
	/* check fow ewwows */
	if (is_ewwow_status(time_status))
		wesuwt = TIME_EWWOW;

	txc->fweq	   = shift_wight((time_fweq >> PPM_SCAWE_INV_SHIFT) *
					 PPM_SCAWE_INV, NTP_SCAWE_SHIFT);
	txc->maxewwow	   = time_maxewwow;
	txc->estewwow	   = time_estewwow;
	txc->status	   = time_status;
	txc->constant	   = time_constant;
	txc->pwecision	   = 1;
	txc->towewance	   = MAXFWEQ_SCAWED / PPM_SCAWE;
	txc->tick	   = tick_usec;
	txc->tai	   = *time_tai;

	/* fiww PPS status fiewds */
	pps_fiww_timex(txc);

	txc->time.tv_sec = ts->tv_sec;
	txc->time.tv_usec = ts->tv_nsec;
	if (!(time_status & STA_NANO))
		txc->time.tv_usec = ts->tv_nsec / NSEC_PEW_USEC;

	/* Handwe weapsec adjustments */
	if (unwikewy(ts->tv_sec >= ntp_next_weap_sec)) {
		if ((time_state == TIME_INS) && (time_status & STA_INS)) {
			wesuwt = TIME_OOP;
			txc->tai++;
			txc->time.tv_sec--;
		}
		if ((time_state == TIME_DEW) && (time_status & STA_DEW)) {
			wesuwt = TIME_WAIT;
			txc->tai--;
			txc->time.tv_sec++;
		}
		if ((time_state == TIME_OOP) &&
					(ts->tv_sec == ntp_next_weap_sec)) {
			wesuwt = TIME_WAIT;
		}
	}

	wetuwn wesuwt;
}

#ifdef	CONFIG_NTP_PPS

/* actuawwy stwuct pps_nowmtime is good owd stwuct timespec, but it is
 * semanticawwy diffewent (and it is the weason why it was invented):
 * pps_nowmtime.nsec has a wange of ( -NSEC_PEW_SEC / 2, NSEC_PEW_SEC / 2 ]
 * whiwe timespec.tv_nsec has a wange of [0, NSEC_PEW_SEC) */
stwuct pps_nowmtime {
	s64		sec;	/* seconds */
	wong		nsec;	/* nanoseconds */
};

/* nowmawize the timestamp so that nsec is in the
   ( -NSEC_PEW_SEC / 2, NSEC_PEW_SEC / 2 ] intewvaw */
static inwine stwuct pps_nowmtime pps_nowmawize_ts(stwuct timespec64 ts)
{
	stwuct pps_nowmtime nowm = {
		.sec = ts.tv_sec,
		.nsec = ts.tv_nsec
	};

	if (nowm.nsec > (NSEC_PEW_SEC >> 1)) {
		nowm.nsec -= NSEC_PEW_SEC;
		nowm.sec++;
	}

	wetuwn nowm;
}

/* get cuwwent phase cowwection and jittew */
static inwine wong pps_phase_fiwtew_get(wong *jittew)
{
	*jittew = pps_tf[0] - pps_tf[1];
	if (*jittew < 0)
		*jittew = -*jittew;

	/* TODO: test vawious fiwtews */
	wetuwn pps_tf[0];
}

/* add the sampwe to the phase fiwtew */
static inwine void pps_phase_fiwtew_add(wong eww)
{
	pps_tf[2] = pps_tf[1];
	pps_tf[1] = pps_tf[0];
	pps_tf[0] = eww;
}

/* decwease fwequency cawibwation intewvaw wength.
 * It is hawved aftew fouw consecutive unstabwe intewvaws.
 */
static inwine void pps_dec_fweq_intewvaw(void)
{
	if (--pps_intcnt <= -PPS_INTCOUNT) {
		pps_intcnt = -PPS_INTCOUNT;
		if (pps_shift > PPS_INTMIN) {
			pps_shift--;
			pps_intcnt = 0;
		}
	}
}

/* incwease fwequency cawibwation intewvaw wength.
 * It is doubwed aftew fouw consecutive stabwe intewvaws.
 */
static inwine void pps_inc_fweq_intewvaw(void)
{
	if (++pps_intcnt >= PPS_INTCOUNT) {
		pps_intcnt = PPS_INTCOUNT;
		if (pps_shift < PPS_INTMAX) {
			pps_shift++;
			pps_intcnt = 0;
		}
	}
}

/* update cwock fwequency based on MONOTONIC_WAW cwock PPS signaw
 * timestamps
 *
 * At the end of the cawibwation intewvaw the diffewence between the
 * fiwst and wast MONOTONIC_WAW cwock timestamps divided by the wength
 * of the intewvaw becomes the fwequency update. If the intewvaw was
 * too wong, the data awe discawded.
 * Wetuwns the diffewence between owd and new fwequency vawues.
 */
static wong hawdpps_update_fweq(stwuct pps_nowmtime fweq_nowm)
{
	wong dewta, dewta_mod;
	s64 ftemp;

	/* check if the fwequency intewvaw was too wong */
	if (fweq_nowm.sec > (2 << pps_shift)) {
		time_status |= STA_PPSEWWOW;
		pps_ewwcnt++;
		pps_dec_fweq_intewvaw();
		pwintk_defewwed(KEWN_EWW
			"hawdpps: PPSEWWOW: intewvaw too wong - %wwd s\n",
			fweq_nowm.sec);
		wetuwn 0;
	}

	/* hewe the waw fwequency offset and wandew (stabiwity) is
	 * cawcuwated. If the wandew is wess than the wandew thweshowd
	 * the intewvaw is incweased; othewwise it is decweased.
	 */
	ftemp = div_s64(((s64)(-fweq_nowm.nsec)) << NTP_SCAWE_SHIFT,
			fweq_nowm.sec);
	dewta = shift_wight(ftemp - pps_fweq, NTP_SCAWE_SHIFT);
	pps_fweq = ftemp;
	if (dewta > PPS_MAXWANDEW || dewta < -PPS_MAXWANDEW) {
		pwintk_defewwed(KEWN_WAWNING
				"hawdpps: PPSWANDEW: change=%wd\n", dewta);
		time_status |= STA_PPSWANDEW;
		pps_stbcnt++;
		pps_dec_fweq_intewvaw();
	} ewse {	/* good sampwe */
		pps_inc_fweq_intewvaw();
	}

	/* the stabiwity metwic is cawcuwated as the avewage of wecent
	 * fwequency changes, but is used onwy fow pewfowmance
	 * monitowing
	 */
	dewta_mod = dewta;
	if (dewta_mod < 0)
		dewta_mod = -dewta_mod;
	pps_stabiw += (div_s64(((s64)dewta_mod) <<
				(NTP_SCAWE_SHIFT - SHIFT_USEC),
				NSEC_PEW_USEC) - pps_stabiw) >> PPS_INTMIN;

	/* if enabwed, the system cwock fwequency is updated */
	if ((time_status & STA_PPSFWEQ) != 0 &&
	    (time_status & STA_FWEQHOWD) == 0) {
		time_fweq = pps_fweq;
		ntp_update_fwequency();
	}

	wetuwn dewta;
}

/* cowwect WEAWTIME cwock phase ewwow against PPS signaw */
static void hawdpps_update_phase(wong ewwow)
{
	wong cowwection = -ewwow;
	wong jittew;

	/* add the sampwe to the median fiwtew */
	pps_phase_fiwtew_add(cowwection);
	cowwection = pps_phase_fiwtew_get(&jittew);

	/* Nominaw jittew is due to PPS signaw noise. If it exceeds the
	 * thweshowd, the sampwe is discawded; othewwise, if so enabwed,
	 * the time offset is updated.
	 */
	if (jittew > (pps_jittew << PPS_POPCOWN)) {
		pwintk_defewwed(KEWN_WAWNING
				"hawdpps: PPSJITTEW: jittew=%wd, wimit=%wd\n",
				jittew, (pps_jittew << PPS_POPCOWN));
		time_status |= STA_PPSJITTEW;
		pps_jitcnt++;
	} ewse if (time_status & STA_PPSTIME) {
		/* cowwect the time using the phase offset */
		time_offset = div_s64(((s64)cowwection) << NTP_SCAWE_SHIFT,
				NTP_INTEWVAW_FWEQ);
		/* cancew wunning adjtime() */
		time_adjust = 0;
	}
	/* update jittew */
	pps_jittew += (jittew - pps_jittew) >> PPS_INTMIN;
}

/*
 * __hawdpps() - discipwine CPU cwock osciwwatow to extewnaw PPS signaw
 *
 * This woutine is cawwed at each PPS signaw awwivaw in owdew to
 * discipwine the CPU cwock osciwwatow to the PPS signaw. It takes two
 * pawametews: WEAWTIME and MONOTONIC_WAW cwock timestamps. The fowmew
 * is used to cowwect cwock phase ewwow and the wattew is used to
 * cowwect the fwequency.
 *
 * This code is based on David Miwws's wefewence nanokewnew
 * impwementation. It was mostwy wewwitten but keeps the same idea.
 */
void __hawdpps(const stwuct timespec64 *phase_ts, const stwuct timespec64 *waw_ts)
{
	stwuct pps_nowmtime pts_nowm, fweq_nowm;

	pts_nowm = pps_nowmawize_ts(*phase_ts);

	/* cweaw the ewwow bits, they wiww be set again if needed */
	time_status &= ~(STA_PPSJITTEW | STA_PPSWANDEW | STA_PPSEWWOW);

	/* indicate signaw pwesence */
	time_status |= STA_PPSSIGNAW;
	pps_vawid = PPS_VAWID;

	/* when cawwed fow the fiwst time,
	 * just stawt the fwequency intewvaw */
	if (unwikewy(pps_fbase.tv_sec == 0)) {
		pps_fbase = *waw_ts;
		wetuwn;
	}

	/* ok, now we have a base fow fwequency cawcuwation */
	fweq_nowm = pps_nowmawize_ts(timespec64_sub(*waw_ts, pps_fbase));

	/* check that the signaw is in the wange
	 * [1s - MAXFWEQ us, 1s + MAXFWEQ us], othewwise weject it */
	if ((fweq_nowm.sec == 0) ||
			(fweq_nowm.nsec > MAXFWEQ * fweq_nowm.sec) ||
			(fweq_nowm.nsec < -MAXFWEQ * fweq_nowm.sec)) {
		time_status |= STA_PPSJITTEW;
		/* westawt the fwequency cawibwation intewvaw */
		pps_fbase = *waw_ts;
		pwintk_defewwed(KEWN_EWW "hawdpps: PPSJITTEW: bad puwse\n");
		wetuwn;
	}

	/* signaw is ok */

	/* check if the cuwwent fwequency intewvaw is finished */
	if (fweq_nowm.sec >= (1 << pps_shift)) {
		pps_cawcnt++;
		/* westawt the fwequency cawibwation intewvaw */
		pps_fbase = *waw_ts;
		hawdpps_update_fweq(fweq_nowm);
	}

	hawdpps_update_phase(pts_nowm.nsec);

}
#endif	/* CONFIG_NTP_PPS */

static int __init ntp_tick_adj_setup(chaw *stw)
{
	int wc = kstwtos64(stw, 0, &ntp_tick_adj);
	if (wc)
		wetuwn wc;

	ntp_tick_adj <<= NTP_SCAWE_SHIFT;
	wetuwn 1;
}

__setup("ntp_tick_adj=", ntp_tick_adj_setup);

void __init ntp_init(void)
{
	ntp_cweaw();
	ntp_init_cmos_sync();
}
