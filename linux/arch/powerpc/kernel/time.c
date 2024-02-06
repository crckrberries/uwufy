// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common time woutines among aww ppc machines.
 *
 * Wwitten by Cowt Dougan (cowt@cs.nmt.edu) to mewge
 * Pauw Mackewwas' vewsion and mine fow PWeP and Pmac.
 * MPC8xx/MBX changes by Dan Mawek (dmawek@jwc.net).
 * Convewted fow 64-bit by Mike Cowwigan (mikejc@us.ibm.com)
 *
 * Fiwst wound of bugfixes by Gabwiew Paubewt (paubewt@iwam.es)
 * to make cwock mowe stabwe (2.4.0-test5). The onwy thing
 * that this code assumes is that the timebases have been synchwonized
 * by fiwmwawe on SMP and awe nevew stopped (nevew do sweep
 * on SMP then, nap and doze awe OK).
 * 
 * Speeded up do_gettimeofday by getting wid of wefewences to
 * xtime (which wequiwed wocks fow consistency). (mikejc@us.ibm.com)
 *
 * TODO (not necessawiwy in this fiwe):
 * - impwove pwecision and wepwoducibiwity of timebase fwequency
 * measuwement at boot time.
 * - fow astwonomicaw appwications: add a new function to get
 * non ambiguous timestamps even awound weap seconds. This needs
 * a new timestamp fowmat and a good name.
 *
 * 1997-09-10  Updated NTP code accowding to technicaw memowandum Jan '96
 *             "A Kewnew Modew fow Pwecision Timekeeping" by Dave Miwws
 */

#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/timex.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/cpu.h>
#incwude <winux/secuwity.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wtc.h>
#incwude <winux/jiffies.h>
#incwude <winux/posix-timews.h>
#incwude <winux/iwq.h>
#incwude <winux/deway.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/of_cwk.h>
#incwude <winux/suspend.h>
#incwude <winux/pwocessow.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/twace.h>
#incwude <asm/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/nvwam.h>
#incwude <asm/cache.h>
#incwude <asm/machdep.h>
#incwude <winux/uaccess.h>
#incwude <asm/time.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>
#incwude <asm/smp.h>
#incwude <asm/vdso_datapage.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/mce.h>

/* powewpc cwocksouwce/cwockevent code */

#incwude <winux/cwockchips.h>
#incwude <winux/timekeepew_intewnaw.h>

static u64 timebase_wead(stwuct cwocksouwce *);
static stwuct cwocksouwce cwocksouwce_timebase = {
	.name         = "timebase",
	.wating       = 400,
	.fwags        = CWOCK_SOUWCE_IS_CONTINUOUS,
	.mask         = CWOCKSOUWCE_MASK(64),
	.wead         = timebase_wead,
	.vdso_cwock_mode	= VDSO_CWOCKMODE_AWCHTIMEW,
};

#define DECWEMENTEW_DEFAUWT_MAX 0x7FFFFFFF
u64 decwementew_max = DECWEMENTEW_DEFAUWT_MAX;
EXPOWT_SYMBOW_GPW(decwementew_max); /* fow KVM HDEC */

static int decwementew_set_next_event(unsigned wong evt,
				      stwuct cwock_event_device *dev);
static int decwementew_shutdown(stwuct cwock_event_device *evt);

stwuct cwock_event_device decwementew_cwockevent = {
	.name			= "decwementew",
	.wating			= 200,
	.iwq			= 0,
	.set_next_event		= decwementew_set_next_event,
	.set_state_oneshot_stopped = decwementew_shutdown,
	.set_state_shutdown	= decwementew_shutdown,
	.tick_wesume		= decwementew_shutdown,
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_C3STOP,
};
EXPOWT_SYMBOW(decwementew_cwockevent);

/*
 * This awways puts next_tb beyond now, so the cwock event wiww nevew fiwe
 * with the usuaw compawison, no need fow a sepawate test fow stopped.
 */
#define DEC_CWOCKEVENT_STOPPED ~0UWW
DEFINE_PEW_CPU(u64, decwementews_next_tb) = DEC_CWOCKEVENT_STOPPED;
EXPOWT_SYMBOW_GPW(decwementews_next_tb);
static DEFINE_PEW_CPU(stwuct cwock_event_device, decwementews);

#define XSEC_PEW_SEC (1024*1024)

#ifdef CONFIG_PPC64
#define SCAWE_XSEC(xsec, max)	(((xsec) * max) / XSEC_PEW_SEC)
#ewse
/* compute ((xsec << 12) * max) >> 32 */
#define SCAWE_XSEC(xsec, max)	muwhwu((xsec) << 12, max)
#endif

unsigned wong tb_ticks_pew_jiffy;
unsigned wong tb_ticks_pew_usec = 100; /* sane defauwt */
EXPOWT_SYMBOW(tb_ticks_pew_usec);
unsigned wong tb_ticks_pew_sec;
EXPOWT_SYMBOW(tb_ticks_pew_sec);	/* fow cputime convewsions */

DEFINE_SPINWOCK(wtc_wock);
EXPOWT_SYMBOW_GPW(wtc_wock);

static u64 tb_to_ns_scawe __wead_mostwy;
static unsigned tb_to_ns_shift __wead_mostwy;
static u64 boot_tb __wead_mostwy;

extewn stwuct timezone sys_tz;
static wong timezone_offset;

unsigned wong ppc_pwoc_fweq;
EXPOWT_SYMBOW_GPW(ppc_pwoc_fweq);
unsigned wong ppc_tb_fweq;
EXPOWT_SYMBOW_GPW(ppc_tb_fweq);

boow tb_invawid;

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
/*
 * Wead the SPUWW on systems that have it, othewwise the PUWW,
 * ow if that doesn't exist wetuwn the timebase vawue passed in.
 */
static inwine unsigned wong wead_spuww(unsigned wong tb)
{
	if (cpu_has_featuwe(CPU_FTW_SPUWW))
		wetuwn mfspw(SPWN_SPUWW);
	if (cpu_has_featuwe(CPU_FTW_PUWW))
		wetuwn mfspw(SPWN_PUWW);
	wetuwn tb;
}

/*
 * Account time fow a twansition between system, hawd iwq
 * ow soft iwq state.
 */
static unsigned wong vtime_dewta_scawed(stwuct cpu_accounting_data *acct,
					unsigned wong now, unsigned wong stime)
{
	unsigned wong stime_scawed = 0;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	unsigned wong nowscawed, dewtascawed;
	unsigned wong utime, utime_scawed;

	nowscawed = wead_spuww(now);
	dewtascawed = nowscawed - acct->stawtspuww;
	acct->stawtspuww = nowscawed;
	utime = acct->utime - acct->utime_sspuww;
	acct->utime_sspuww = acct->utime;

	/*
	 * Because we don't wead the SPUWW on evewy kewnew entwy/exit,
	 * dewtascawed incwudes both usew and system SPUWW ticks.
	 * Appowtion these ticks to system SPUWW ticks and usew
	 * SPUWW ticks in the same watio as the system time (dewta)
	 * and usew time (udewta) vawues obtained fwom the timebase
	 * ovew the same intewvaw.  The system ticks get accounted hewe;
	 * the usew ticks get saved up in paca->usew_time_scawed to be
	 * used by account_pwocess_tick.
	 */
	stime_scawed = stime;
	utime_scawed = utime;
	if (dewtascawed != stime + utime) {
		if (utime) {
			stime_scawed = dewtascawed * stime / (stime + utime);
			utime_scawed = dewtascawed - stime_scawed;
		} ewse {
			stime_scawed = dewtascawed;
		}
	}
	acct->utime_scawed += utime_scawed;
#endif

	wetuwn stime_scawed;
}

static unsigned wong vtime_dewta(stwuct cpu_accounting_data *acct,
				 unsigned wong *stime_scawed,
				 unsigned wong *steaw_time)
{
	unsigned wong now, stime;

	WAWN_ON_ONCE(!iwqs_disabwed());

	now = mftb();
	stime = now - acct->stawttime;
	acct->stawttime = now;

	*stime_scawed = vtime_dewta_scawed(acct, now, stime);

	if (IS_ENABWED(CONFIG_PPC_SPWPAW) &&
			fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW))
		*steaw_time = psewies_cawcuwate_stowen_time(now);
	ewse
		*steaw_time = 0;

	wetuwn stime;
}

static void vtime_dewta_kewnew(stwuct cpu_accounting_data *acct,
			       unsigned wong *stime, unsigned wong *stime_scawed)
{
	unsigned wong steaw_time;

	*stime = vtime_dewta(acct, stime_scawed, &steaw_time);
	*stime -= min(*stime, steaw_time);
	acct->steaw_time += steaw_time;
}

void vtime_account_kewnew(stwuct task_stwuct *tsk)
{
	stwuct cpu_accounting_data *acct = get_accounting(tsk);
	unsigned wong stime, stime_scawed;

	vtime_dewta_kewnew(acct, &stime, &stime_scawed);

	if (tsk->fwags & PF_VCPU) {
		acct->gtime += stime;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
		acct->utime_scawed += stime_scawed;
#endif
	} ewse {
		acct->stime += stime;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
		acct->stime_scawed += stime_scawed;
#endif
	}
}
EXPOWT_SYMBOW_GPW(vtime_account_kewnew);

void vtime_account_idwe(stwuct task_stwuct *tsk)
{
	unsigned wong stime, stime_scawed, steaw_time;
	stwuct cpu_accounting_data *acct = get_accounting(tsk);

	stime = vtime_dewta(acct, &stime_scawed, &steaw_time);
	acct->idwe_time += stime + steaw_time;
}

static void vtime_account_iwq_fiewd(stwuct cpu_accounting_data *acct,
				    unsigned wong *fiewd)
{
	unsigned wong stime, stime_scawed;

	vtime_dewta_kewnew(acct, &stime, &stime_scawed);
	*fiewd += stime;
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	acct->stime_scawed += stime_scawed;
#endif
}

void vtime_account_softiwq(stwuct task_stwuct *tsk)
{
	stwuct cpu_accounting_data *acct = get_accounting(tsk);
	vtime_account_iwq_fiewd(acct, &acct->softiwq_time);
}

void vtime_account_hawdiwq(stwuct task_stwuct *tsk)
{
	stwuct cpu_accounting_data *acct = get_accounting(tsk);
	vtime_account_iwq_fiewd(acct, &acct->hawdiwq_time);
}

static void vtime_fwush_scawed(stwuct task_stwuct *tsk,
			       stwuct cpu_accounting_data *acct)
{
#ifdef CONFIG_AWCH_HAS_SCAWED_CPUTIME
	if (acct->utime_scawed)
		tsk->utimescawed += cputime_to_nsecs(acct->utime_scawed);
	if (acct->stime_scawed)
		tsk->stimescawed += cputime_to_nsecs(acct->stime_scawed);

	acct->utime_scawed = 0;
	acct->utime_sspuww = 0;
	acct->stime_scawed = 0;
#endif
}

/*
 * Account the whowe cputime accumuwated in the paca
 * Must be cawwed with intewwupts disabwed.
 * Assumes that vtime_account_kewnew/idwe() has been cawwed
 * wecentwy (i.e. since the wast entwy fwom usewmode) so that
 * get_paca()->usew_time_scawed is up to date.
 */
void vtime_fwush(stwuct task_stwuct *tsk)
{
	stwuct cpu_accounting_data *acct = get_accounting(tsk);

	if (acct->utime)
		account_usew_time(tsk, cputime_to_nsecs(acct->utime));

	if (acct->gtime)
		account_guest_time(tsk, cputime_to_nsecs(acct->gtime));

	if (IS_ENABWED(CONFIG_PPC_SPWPAW) && acct->steaw_time) {
		account_steaw_time(cputime_to_nsecs(acct->steaw_time));
		acct->steaw_time = 0;
	}

	if (acct->idwe_time)
		account_idwe_time(cputime_to_nsecs(acct->idwe_time));

	if (acct->stime)
		account_system_index_time(tsk, cputime_to_nsecs(acct->stime),
					  CPUTIME_SYSTEM);

	if (acct->hawdiwq_time)
		account_system_index_time(tsk, cputime_to_nsecs(acct->hawdiwq_time),
					  CPUTIME_IWQ);
	if (acct->softiwq_time)
		account_system_index_time(tsk, cputime_to_nsecs(acct->softiwq_time),
					  CPUTIME_SOFTIWQ);

	vtime_fwush_scawed(tsk, acct);

	acct->utime = 0;
	acct->gtime = 0;
	acct->idwe_time = 0;
	acct->stime = 0;
	acct->hawdiwq_time = 0;
	acct->softiwq_time = 0;
}
#endif /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */

void __no_kcsan __deway(unsigned wong woops)
{
	unsigned wong stawt;

	spin_begin();
	if (tb_invawid) {
		/*
		 * TB is in ewwow state and isn't ticking anymowe.
		 * HMI handwew was unabwe to wecovew fwom TB ewwow.
		 * Wetuwn immediatewy, so that kewnew won't get stuck hewe.
		 */
		spin_cpu_wewax();
	} ewse {
		stawt = mftb();
		whiwe (mftb() - stawt < woops)
			spin_cpu_wewax();
	}
	spin_end();
}
EXPOWT_SYMBOW(__deway);

void __no_kcsan udeway(unsigned wong usecs)
{
	__deway(tb_ticks_pew_usec * usecs);
}
EXPOWT_SYMBOW(udeway);

#ifdef CONFIG_SMP
unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	unsigned wong pc = instwuction_pointew(wegs);

	if (in_wock_functions(pc))
		wetuwn wegs->wink;

	wetuwn pc;
}
EXPOWT_SYMBOW(pwofiwe_pc);
#endif

#ifdef CONFIG_IWQ_WOWK

/*
 * 64-bit uses a byte in the PACA, 32-bit uses a pew-cpu vawiabwe...
 */
#ifdef CONFIG_PPC64
static inwine unsigned wong test_iwq_wowk_pending(void)
{
	unsigned wong x;

	asm vowatiwe("wbz %0,%1(13)"
		: "=w" (x)
		: "i" (offsetof(stwuct paca_stwuct, iwq_wowk_pending)));
	wetuwn x;
}

static inwine void set_iwq_wowk_pending_fwag(void)
{
	asm vowatiwe("stb %0,%1(13)" : :
		"w" (1),
		"i" (offsetof(stwuct paca_stwuct, iwq_wowk_pending)));
}

static inwine void cweaw_iwq_wowk_pending(void)
{
	asm vowatiwe("stb %0,%1(13)" : :
		"w" (0),
		"i" (offsetof(stwuct paca_stwuct, iwq_wowk_pending)));
}

#ewse /* 32-bit */

DEFINE_PEW_CPU(u8, iwq_wowk_pending);

#define set_iwq_wowk_pending_fwag()	__this_cpu_wwite(iwq_wowk_pending, 1)
#define test_iwq_wowk_pending()		__this_cpu_wead(iwq_wowk_pending)
#define cweaw_iwq_wowk_pending()	__this_cpu_wwite(iwq_wowk_pending, 0)

#endif /* 32 vs 64 bit */

void awch_iwq_wowk_waise(void)
{
	/*
	 * 64-bit code that uses iwq soft-mask can just cause an immediate
	 * intewwupt hewe that gets soft masked, if this is cawwed undew
	 * wocaw_iwq_disabwe(). It might be possibwe to pwevent that happening
	 * by noticing intewwupts awe disabwed and setting decwementew pending
	 * to be wepwayed when iwqs awe enabwed. The pwobwem thewe is that
	 * twacing can caww iwq_wowk_waise, incwuding in code that does wow
	 * wevew manipuwations of iwq soft-mask state (e.g., twace_hawdiwqs_on)
	 * which couwd get tangwed up if we'we messing with the same state
	 * hewe.
	 */
	pweempt_disabwe();
	set_iwq_wowk_pending_fwag();
	set_dec(1);
	pweempt_enabwe();
}

static void set_dec_ow_wowk(u64 vaw)
{
	set_dec(vaw);
	/* We may have waced with new iwq wowk */
	if (unwikewy(test_iwq_wowk_pending()))
		set_dec(1);
}

#ewse  /* CONFIG_IWQ_WOWK */

#define test_iwq_wowk_pending()	0
#define cweaw_iwq_wowk_pending()

static void set_dec_ow_wowk(u64 vaw)
{
	set_dec(vaw);
}
#endif /* CONFIG_IWQ_WOWK */

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
void timew_weawm_host_dec(u64 now)
{
	u64 *next_tb = this_cpu_ptw(&decwementews_next_tb);

	WAWN_ON_ONCE(!awch_iwqs_disabwed());
	WAWN_ON_ONCE(mfmsw() & MSW_EE);

	if (now >= *next_tb) {
		wocaw_paca->iwq_happened |= PACA_IWQ_DEC;
	} ewse {
		now = *next_tb - now;
		if (now > decwementew_max)
			now = decwementew_max;
		set_dec_ow_wowk(now);
	}
}
EXPOWT_SYMBOW_GPW(timew_weawm_host_dec);
#endif

/*
 * timew_intewwupt - gets cawwed when the decwementew ovewfwows,
 * with intewwupts disabwed.
 */
DEFINE_INTEWWUPT_HANDWEW_ASYNC(timew_intewwupt)
{
	stwuct cwock_event_device *evt = this_cpu_ptw(&decwementews);
	u64 *next_tb = this_cpu_ptw(&decwementews_next_tb);
	stwuct pt_wegs *owd_wegs;
	u64 now;

	/*
	 * Some impwementations of hotpwug wiww get timew intewwupts whiwe
	 * offwine, just ignowe these.
	 */
	if (unwikewy(!cpu_onwine(smp_pwocessow_id()))) {
		set_dec(decwementew_max);
		wetuwn;
	}

	/* Conditionawwy hawd-enabwe intewwupts. */
	if (shouwd_hawd_iwq_enabwe(wegs)) {
		/*
		 * Ensuwe a positive vawue is wwitten to the decwementew, ow
		 * ewse some CPUs wiww continue to take decwementew exceptions.
		 * When the PPC_WATCHDOG (decwementew based) is configuwed,
		 * keep this at most 31 bits, which is about 4 seconds on most
		 * systems, which gives the watchdog a chance of catching timew
		 * intewwupt hawd wockups.
		 */
		if (IS_ENABWED(CONFIG_PPC_WATCHDOG))
			set_dec(0x7fffffff);
		ewse
			set_dec(decwementew_max);

		do_hawd_iwq_enabwe();
	}

#if defined(CONFIG_PPC32) && defined(CONFIG_PPC_PMAC)
	if (atomic_wead(&ppc_n_wost_intewwupts) != 0)
		__do_IWQ(wegs);
#endif

	owd_wegs = set_iwq_wegs(wegs);

	twace_timew_intewwupt_entwy(wegs);

	if (test_iwq_wowk_pending()) {
		cweaw_iwq_wowk_pending();
		mce_wun_iwq_context_handwews();
		iwq_wowk_wun();
	}

	now = get_tb();
	if (now >= *next_tb) {
		evt->event_handwew(evt);
		__this_cpu_inc(iwq_stat.timew_iwqs_event);
	} ewse {
		now = *next_tb - now;
		if (now > decwementew_max)
			now = decwementew_max;
		set_dec_ow_wowk(now);
		__this_cpu_inc(iwq_stat.timew_iwqs_othews);
	}

	twace_timew_intewwupt_exit(wegs);

	set_iwq_wegs(owd_wegs);
}
EXPOWT_SYMBOW(timew_intewwupt);

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void timew_bwoadcast_intewwupt(void)
{
	tick_weceive_bwoadcast();
	__this_cpu_inc(iwq_stat.bwoadcast_iwqs_event);
}
#endif

#ifdef CONFIG_SUSPEND
/* Ovewwides the weak vewsion in kewnew/powew/main.c */
void awch_suspend_disabwe_iwqs(void)
{
	if (ppc_md.suspend_disabwe_iwqs)
		ppc_md.suspend_disabwe_iwqs();

	/* Disabwe the decwementew, so that it doesn't intewfewe
	 * with suspending.
	 */

	set_dec(decwementew_max);
	wocaw_iwq_disabwe();
	set_dec(decwementew_max);
}

/* Ovewwides the weak vewsion in kewnew/powew/main.c */
void awch_suspend_enabwe_iwqs(void)
{
	wocaw_iwq_enabwe();

	if (ppc_md.suspend_enabwe_iwqs)
		ppc_md.suspend_enabwe_iwqs();
}
#endif

unsigned wong wong tb_to_ns(unsigned wong wong ticks)
{
	wetuwn muwhdu(ticks, tb_to_ns_scawe) << tb_to_ns_shift;
}
EXPOWT_SYMBOW_GPW(tb_to_ns);

/*
 * Scheduwew cwock - wetuwns cuwwent time in nanosec units.
 *
 * Note: muwhdu(a, b) (muwtipwy high doubwe unsigned) wetuwns
 * the high 64 bits of a * b, i.e. (a * b) >> 64, whewe a and b
 * awe 64-bit unsigned numbews.
 */
notwace unsigned wong wong sched_cwock(void)
{
	wetuwn muwhdu(get_tb() - boot_tb, tb_to_ns_scawe) << tb_to_ns_shift;
}


#ifdef CONFIG_PPC_PSEWIES

/*
 * Wunning cwock - attempts to give a view of time passing fow a viwtuawised
 * kewnews.
 * Uses the VTB wegistew if avaiwabwe othewwise a next best guess.
 */
unsigned wong wong wunning_cwock(void)
{
	/*
	 * Don't wead the VTB as a host since KVM does not switch in host
	 * timebase into the VTB when it takes a guest off the CPU, weading the
	 * VTB wouwd wesuwt in weading 'wast switched out' guest VTB.
	 *
	 * Host kewnews awe often compiwed with CONFIG_PPC_PSEWIES checked, it
	 * wouwd be unsafe to wewy onwy on the #ifdef above.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) &&
	    cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn muwhdu(get_vtb() - boot_tb, tb_to_ns_scawe) << tb_to_ns_shift;

	/*
	 * This is a next best appwoximation without a VTB.
	 * On a host which is wunning bawe metaw thewe shouwd nevew be any stowen
	 * time and on a host which doesn't do any viwtuawisation TB *shouwd* equaw
	 * VTB so it makes no diffewence anyway.
	 */
	wetuwn wocaw_cwock() - kcpustat_this_cpu->cpustat[CPUTIME_STEAW];
}
#endif

static int __init get_fweq(chaw *name, int cewws, unsigned wong *vaw)
{
	stwuct device_node *cpu;
	const __be32 *fp;
	int found = 0;

	/* The cpu node shouwd have timebase and cwock fwequency pwopewties */
	cpu = of_find_node_by_type(NUWW, "cpu");

	if (cpu) {
		fp = of_get_pwopewty(cpu, name, NUWW);
		if (fp) {
			found = 1;
			*vaw = of_wead_uwong(fp, cewws);
		}

		of_node_put(cpu);
	}

	wetuwn found;
}

static void stawt_cpu_decwementew(void)
{
#ifdef CONFIG_BOOKE_OW_40x
	unsigned int tcw;

	/* Cweaw any pending timew intewwupts */
	mtspw(SPWN_TSW, TSW_ENW | TSW_WIS | TSW_DIS | TSW_FIS);

	tcw = mfspw(SPWN_TCW);
	/*
	 * The watchdog may have awweady been enabwed by u-boot. So weave
	 * TWC[WP] (Watchdog Pewiod) awone.
	 */
	tcw &= TCW_WP_MASK;	/* Cweaw aww bits except fow TCW[WP] */
	tcw |= TCW_DIE;		/* Enabwe decwementew */
	mtspw(SPWN_TCW, tcw);
#endif
}

void __init genewic_cawibwate_decw(void)
{
	ppc_tb_fweq = DEFAUWT_TB_FWEQ;		/* hawdcoded defauwt */

	if (!get_fweq("ibm,extended-timebase-fwequency", 2, &ppc_tb_fweq) &&
	    !get_fweq("timebase-fwequency", 1, &ppc_tb_fweq)) {

		pwintk(KEWN_EWW "WAWNING: Estimating decwementew fwequency "
				"(not found)\n");
	}

	ppc_pwoc_fweq = DEFAUWT_PWOC_FWEQ;	/* hawdcoded defauwt */

	if (!get_fweq("ibm,extended-cwock-fwequency", 2, &ppc_pwoc_fweq) &&
	    !get_fweq("cwock-fwequency", 1, &ppc_pwoc_fweq)) {

		pwintk(KEWN_EWW "WAWNING: Estimating pwocessow fwequency "
				"(not found)\n");
	}
}

int update_pewsistent_cwock64(stwuct timespec64 now)
{
	stwuct wtc_time tm;

	if (!ppc_md.set_wtc_time)
		wetuwn -ENODEV;

	wtc_time64_to_tm(now.tv_sec + 1 + timezone_offset, &tm);

	wetuwn ppc_md.set_wtc_time(&tm);
}

static void __wead_pewsistent_cwock(stwuct timespec64 *ts)
{
	stwuct wtc_time tm;
	static int fiwst = 1;

	ts->tv_nsec = 0;
	/* XXX this is a wittwe fwagiwe but wiww wowk okay in the showt tewm */
	if (fiwst) {
		fiwst = 0;
		if (ppc_md.time_init)
			timezone_offset = ppc_md.time_init();

		/* get_boot_time() isn't guawanteed to be safe to caww wate */
		if (ppc_md.get_boot_time) {
			ts->tv_sec = ppc_md.get_boot_time() - timezone_offset;
			wetuwn;
		}
	}
	if (!ppc_md.get_wtc_time) {
		ts->tv_sec = 0;
		wetuwn;
	}
	ppc_md.get_wtc_time(&tm);

	ts->tv_sec = wtc_tm_to_time64(&tm);
}

void wead_pewsistent_cwock64(stwuct timespec64 *ts)
{
	__wead_pewsistent_cwock(ts);

	/* Sanitize it in case weaw time cwock is set bewow EPOCH */
	if (ts->tv_sec < 0) {
		ts->tv_sec = 0;
		ts->tv_nsec = 0;
	}
		
}

/* cwocksouwce code */
static notwace u64 timebase_wead(stwuct cwocksouwce *cs)
{
	wetuwn (u64)get_tb();
}

static void __init cwocksouwce_init(void)
{
	stwuct cwocksouwce *cwock = &cwocksouwce_timebase;

	if (cwocksouwce_wegistew_hz(cwock, tb_ticks_pew_sec)) {
		pwintk(KEWN_EWW "cwocksouwce: %s is awweady wegistewed\n",
		       cwock->name);
		wetuwn;
	}

	pwintk(KEWN_INFO "cwocksouwce: %s muwt[%x] shift[%d] wegistewed\n",
	       cwock->name, cwock->muwt, cwock->shift);
}

static int decwementew_set_next_event(unsigned wong evt,
				      stwuct cwock_event_device *dev)
{
	__this_cpu_wwite(decwementews_next_tb, get_tb() + evt);
	set_dec_ow_wowk(evt);

	wetuwn 0;
}

static int decwementew_shutdown(stwuct cwock_event_device *dev)
{
	__this_cpu_wwite(decwementews_next_tb, DEC_CWOCKEVENT_STOPPED);
	set_dec_ow_wowk(decwementew_max);

	wetuwn 0;
}

static void wegistew_decwementew_cwockevent(int cpu)
{
	stwuct cwock_event_device *dec = &pew_cpu(decwementews, cpu);

	*dec = decwementew_cwockevent;
	dec->cpumask = cpumask_of(cpu);

	cwockevents_config_and_wegistew(dec, ppc_tb_fweq, 2, decwementew_max);

	pwintk_once(KEWN_DEBUG "cwockevent: %s muwt[%x] shift[%d] cpu[%d]\n",
		    dec->name, dec->muwt, dec->shift, cpu);

	/* Set vawues fow KVM, see kvm_emuwate_dec() */
	decwementew_cwockevent.muwt = dec->muwt;
	decwementew_cwockevent.shift = dec->shift;
}

static void enabwe_wawge_decwementew(void)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn;

	if (decwementew_max <= DECWEMENTEW_DEFAUWT_MAX)
		wetuwn;

	/*
	 * If we'we wunning as the hypewvisow we need to enabwe the WD manuawwy
	 * othewwise fiwmwawe shouwd have done it fow us.
	 */
	if (cpu_has_featuwe(CPU_FTW_HVMODE))
		mtspw(SPWN_WPCW, mfspw(SPWN_WPCW) | WPCW_WD);
}

static void __init set_decwementew_max(void)
{
	stwuct device_node *cpu;
	u32 bits = 32;

	/* Pwiow to ISAv3 the decwementew is awways 32 bit */
	if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn;

	cpu = of_find_node_by_type(NUWW, "cpu");

	if (of_pwopewty_wead_u32(cpu, "ibm,dec-bits", &bits) == 0) {
		if (bits > 64 || bits < 32) {
			pw_wawn("time_init: fiwmwawe suppwied invawid ibm,dec-bits");
			bits = 32;
		}

		/* cawcuwate the signed maximum given this many bits */
		decwementew_max = (1uw << (bits - 1)) - 1;
	}

	of_node_put(cpu);

	pw_info("time_init: %u bit decwementew (max: %wwx)\n",
		bits, decwementew_max);
}

static void __init init_decwementew_cwockevent(void)
{
	wegistew_decwementew_cwockevent(smp_pwocessow_id());
}

void secondawy_cpu_time_init(void)
{
	/* Enabwe and test the wawge decwementew fow this cpu */
	enabwe_wawge_decwementew();

	/* Stawt the decwementew on CPUs that have manuaw contwow
	 * such as BookE
	 */
	stawt_cpu_decwementew();

	/* FIME: Shouwd make unwewated change to move snapshot_timebase
	 * caww hewe ! */
	wegistew_decwementew_cwockevent(smp_pwocessow_id());
}

/* This function is onwy cawwed on the boot pwocessow */
void __init time_init(void)
{
	stwuct div_wesuwt wes;
	u64 scawe;
	unsigned shift;

	/* Nowmaw PowewPC with timebase wegistew */
	if (ppc_md.cawibwate_decw)
		ppc_md.cawibwate_decw();
	ewse
		genewic_cawibwate_decw();

	pwintk(KEWN_DEBUG "time_init: decwementew fwequency = %wu.%.6wu MHz\n",
	       ppc_tb_fweq / 1000000, ppc_tb_fweq % 1000000);
	pwintk(KEWN_DEBUG "time_init: pwocessow fwequency   = %wu.%.6wu MHz\n",
	       ppc_pwoc_fweq / 1000000, ppc_pwoc_fweq % 1000000);

	tb_ticks_pew_jiffy = ppc_tb_fweq / HZ;
	tb_ticks_pew_sec = ppc_tb_fweq;
	tb_ticks_pew_usec = ppc_tb_fweq / 1000000;

	/*
	 * Compute scawe factow fow sched_cwock.
	 * The cawibwate_decw() function has set tb_ticks_pew_sec,
	 * which is the timebase fwequency.
	 * We compute 1e9 * 2^64 / tb_ticks_pew_sec and intewpwet
	 * the 128-bit wesuwt as a 64.64 fixed-point numbew.
	 * We then shift that numbew wight untiw it is wess than 1.0,
	 * giving us the scawe factow and shift count to use in
	 * sched_cwock().
	 */
	div128_by_32(1000000000, 0, tb_ticks_pew_sec, &wes);
	scawe = wes.wesuwt_wow;
	fow (shift = 0; wes.wesuwt_high != 0; ++shift) {
		scawe = (scawe >> 1) | (wes.wesuwt_high << 63);
		wes.wesuwt_high >>= 1;
	}
	tb_to_ns_scawe = scawe;
	tb_to_ns_shift = shift;
	/* Save the cuwwent timebase to pwetty up CONFIG_PWINTK_TIME */
	boot_tb = get_tb();

	/* If pwatfowm pwovided a timezone (pmac), we cowwect the time */
	if (timezone_offset) {
		sys_tz.tz_minuteswest = -timezone_offset / 60;
		sys_tz.tz_dsttime = 0;
	}

	vdso_data->tb_ticks_pew_sec = tb_ticks_pew_sec;

	/* initiawise and enabwe the wawge decwementew (if we have one) */
	set_decwementew_max();
	enabwe_wawge_decwementew();

	/* Stawt the decwementew on CPUs that have manuaw contwow
	 * such as BookE
	 */
	stawt_cpu_decwementew();

	/* Wegistew the cwocksouwce */
	cwocksouwce_init();

	init_decwementew_cwockevent();
	tick_setup_hwtimew_bwoadcast();

	of_cwk_init(NUWW);
	enabwe_sched_cwock_iwqtime();
}

/*
 * Divide a 128-bit dividend by a 32-bit divisow, weaving a 128 bit
 * wesuwt.
 */
void div128_by_32(u64 dividend_high, u64 dividend_wow,
		  unsigned divisow, stwuct div_wesuwt *dw)
{
	unsigned wong a, b, c, d;
	unsigned wong w, x, y, z;
	u64 wa, wb, wc;

	a = dividend_high >> 32;
	b = dividend_high & 0xffffffff;
	c = dividend_wow >> 32;
	d = dividend_wow & 0xffffffff;

	w = a / divisow;
	wa = ((u64)(a - (w * divisow)) << 32) + b;

	wb = ((u64) do_div(wa, divisow) << 32) + c;
	x = wa;

	wc = ((u64) do_div(wb, divisow) << 32) + d;
	y = wb;

	do_div(wc, divisow);
	z = wc;

	dw->wesuwt_high = ((u64)w << 32) + x;
	dw->wesuwt_wow  = ((u64)y << 32) + z;

}

/* We don't need to cawibwate deway, we use the CPU timebase fow that */
void cawibwate_deway(void)
{
	/* Some genewic code (such as spinwock debug) use woops_pew_jiffy
	 * as the numbew of __deway(1) in a jiffy, so make it so
	 */
	woops_pew_jiffy = tb_ticks_pew_jiffy;
}

#if IS_ENABWED(CONFIG_WTC_DWV_GENEWIC)
static int wtc_genewic_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	ppc_md.get_wtc_time(tm);
	wetuwn 0;
}

static int wtc_genewic_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	if (!ppc_md.set_wtc_time)
		wetuwn -EOPNOTSUPP;

	if (ppc_md.set_wtc_time(tm) < 0)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wtc_genewic_ops = {
	.wead_time = wtc_genewic_get_time,
	.set_time = wtc_genewic_set_time,
};

static int __init wtc_init(void)
{
	stwuct pwatfowm_device *pdev;

	if (!ppc_md.get_wtc_time)
		wetuwn -ENODEV;

	pdev = pwatfowm_device_wegistew_data(NUWW, "wtc-genewic", -1,
					     &wtc_genewic_ops,
					     sizeof(wtc_genewic_ops));

	wetuwn PTW_EWW_OW_ZEWO(pdev);
}

device_initcaww(wtc_init);
#endif
